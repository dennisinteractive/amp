<?php

/**
 * @file
 * Real time configuration helper file to break out the form components.
 * This file deals with the macro element, in the vendor section of the form.
 */

/**
 * Function to build the macro section of the form.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The form state.
 * @param mixed $vendor_key
 *   The id for the vendor.
 * @param mixed $tag
 *   The dfp tag object.
 */
function _amp_dfp_rtc_build_macros(&$form, &$form_state, $vendor_key, $tag) {
  $form['rtc_config']['wrapper']['vendor'][$vendor_key]['macros'] = array(
    '#type' => 'markup',
    '#tree' => FALSE,
    '#prefix' => '<div id="rtc-macro-table-' . $vendor_key . '">',
    '#suffix' => '</div>',
    '#theme' => 'rtc_macro_settings',
    '#parents' => array(
      'rtc_config',
      'wrapper',
      'vendor',
      $vendor_key,
      'macros',
    ),
  );

  if (isset($tag->settings['rtc_config']['vendor'][$vendor_key]['macros']) && count($tag->settings['rtc_config']['vendor'][$vendor_key]['macros']) > $form_state['num_macros'][$vendor_key]) {
    $form_state['num_macros'][$vendor_key] = count($tag->settings['rtc_config']['vendor'][$vendor_key]['macros']);
  }

  for ($j = 0; $j < $form_state['num_macros'][$vendor_key]; $j++) {
    $form['rtc_config']['wrapper']['vendor'][$vendor_key]['macros'][$j]['macro'] = array(
      '#type' => 'textfield',
      '#value' => isset($tag->settings['rtc_config']['vendor'][$vendor_key]['macros'][$j]['macro']) ? $tag->settings['rtc_config']['vendor'][$vendor_key]['macros'][$j]['macro'] : '',
      '#parents' => array(
        'rtc_config',
        'wrapper',
        'vendor',
        $vendor_key,
        'macros',
        $j,
        'macro',
      ),
    );
    $form['rtc_config']['wrapper']['vendor'][$vendor_key]['macros'][$j]['value'] = array(
      '#type' => 'textfield',
      '#value' => isset($tag->settings['rtc_config']['vendor'][$vendor_key]['macros'][$j]['value']) ? $tag->settings['rtc_config']['vendor'][$vendor_key]['macros'][$j]['value'] : '',
      '#parents' => array(
        'rtc_config',
        'wrapper',
        'vendor',
        $vendor_key,
        'macros',
        $j,
        'value',
      ),
    );
  }

  $form['rtc_config']['wrapper']['vendor'][$vendor_key]['more_macro'] = array(
    '#type' => 'submit',
    '#value' => t('Add vendor macro'),
    '#submit' => array('_amp_dfp_rtc_macro_form_submit'),
    '#parents' => array('rtc_config', 'wrapper', 'vendor', $vendor_key),
    '#limit_validation_errors' => array(),
    '#ajax' => array(
      'callback' => '_amp_dfp_rtc_macro_form_elements_callback',
      'wrapper' => 'rtc-macro-table-' . $vendor_key,
      'effect' => 'fade',
      'method' => 'replace',
    ),
  );
}

/**
 * Theme function for the "macro" form.
 *
 * @param mixed $variables
 *   The variables array.
 */
function theme_rtc_macro_settings($variables) {
  $form = $variables['form'];
  $headers = array(t('Macro'), t('Value'));
  $rows = array();
  foreach (element_children($form) as $key) {

    if (is_numeric($key) && !empty($form[$key]['macro'])) {
      $rows[] = array(
        drupal_render($form[$key]['macro']),
        drupal_render($form[$key]['value']),
      );
    }
  }

  return theme('table', array('header' => $headers, 'rows' => $rows));
}

/**
 * Submit handler for adding another macro.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The form state.
 */
function _amp_dfp_rtc_macro_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['input']['rtc_config'];
  $form_state['num_macros'][$form_state['input']['vendor_key']]++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback for adding more macros to the vendor.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The form state.
 *
 * @return mixed
 *   Next macro.
 */
function _amp_dfp_rtc_macro_form_elements_callback(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['input']['rtc_config'];
  // Load in previous macros.
  $macros = count($form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros']);
  for ($i = 0; $i < $macros; $i++) {
    if (isset($form_state['input']['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]) && !empty($form_state['input']['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]['macro'])) {
      $form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]['macro']['#value'] = $form_state['input']['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]['macro'];
      $form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]['value']['#value'] = $form_state['input']['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'][$i]['value'];
    }
  }

  return $form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'];
}
