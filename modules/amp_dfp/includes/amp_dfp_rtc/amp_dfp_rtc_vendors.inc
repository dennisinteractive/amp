<?php
/**
 * @file real time configuration helper file to break out the form components, this file deals
 * with the vendor element of the form
 */

/**
 * function to build the vendor section of the form.
 *
 * @param $form
 * @param $form_state
 * @param $tag
 */
function _amp_dfp_rtc_build_vendors(&$form, &$form_state, $tag) {
  if (empty($form_state['num_vendors'])) {
    $form_state['num_vendors'] = 1;
  }
  $form['rtc_config']['wrapper'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,
    '#prefix' => '<div id="rtc-vendor-wrapper">',
    '#suffix' => '</div>',
    '#parents' => array('rtc_config', 'wrapper'),
  );

  if (isset($tag->settings['rtc_config']['vendor']) && count($tag->settings['rtc_config']['vendor']) > $form_state['num_vendors']) {
    $form_state['num_vendors'] = count($tag->settings['rtc_config']['vendor']);
  }
  for ($i = 0; $i < $form_state['num_vendors']; $i++) {

    if (empty($form_state['num_macros'][$i])) {
      $form_state['num_macros'][$i] = 1;
    }

    $form['rtc_config']['wrapper']['vendor'][$i] = array(
      '#type' => 'fieldset',
      '#title' => isset($tag->settings['rtc_config']['vendor'][$i]['vendor_name']) ? t('Vendor: ' . $tag->settings['rtc_config']['vendor'][$i]['vendor_name']) : t('Vendor'),
      '#tree' => TRUE,
      '#collapsible' => TRUE,
      '#parents' => array('rtc_config', 'wrapper', 'vendor'),
    );

    $form['rtc_config']['wrapper']['vendor'][$i]['vendor_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Vendor name'),
      '#description' => t('Vendor name.'),
      '#parents' => array('rtc_config', 'wrapper', 'vendor', $i, 'vendor_name'),
      '#value' => isset($tag->settings['rtc_config']['vendor'][$i]['vendor_name']) ? $tag->settings['rtc_config']['vendor'][$i]['vendor_name'] : '',
    );

    $form['rtc_config']['wrapper']['vendor'][$i]['vendor_key'] = array(
      '#type' => 'hidden',
      '#value' => $i,
      '#name' => 'vendor_key'
    );

    // Build Macros.
    form_load_include($form_state, 'inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_macros');
    _amp_dfp_rtc_build_macros($form, $form_state, $i, $tag);

  }
  $form['rtc_config']['button'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,
    '#prefix' => '<div id="rtc-vendor-button">',
    '#suffix' => '</div>',
    '#parents' => array('rtc_config', 'wrapper'),
  );
  $form['rtc_config']['button']['more_rtc_vendors'] = array(
    '#type' => 'submit',
    '#value' => t('Add vendor'),
    '#submit' => array('_amp_dfp_rtc_vendor_form_submit'),
    '#parents' => array('rtc_config'),
    '#suffix' => '&nbsp;',
    '#ajax' => array(
      'callback' => '_amp_dfp_rtc_vendor_form_elements_callback',
      'wrapper' => 'rtc-vendor-wrapper',
      'effect' => 'fade',
      'method' => 'append',
    ),
  );
}

/**
 * Submit handler for ajax updates to the form.
 * 
 * @param type $form
 * @param type $form_state
 */
function _amp_dfp_rtc_vendor_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['values']['rtc_config'];
  $form_state['num_vendors']++;

  $form_state['rebuild'] = TRUE;
}

/**
 * ajax callback for adding another vendor.
 * 
 * @param type $form
 * @param type $form_state
 * @return type vendor
 */
function _amp_dfp_rtc_vendor_form_elements_callback(&$form, &$form_state) {
  $key = $form_state['input']['vendor_key'] + 1;

  return $form['rtc_config']['wrapper']['vendor'][$key];
}
