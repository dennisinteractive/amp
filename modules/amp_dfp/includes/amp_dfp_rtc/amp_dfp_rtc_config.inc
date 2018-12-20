<?php
/**
 * @file todo
 */

/**
 * todo
 *
 * @param $form
 * @param $form_state
 * @param $tag
 */
function _amp_dfp_rtc_configuration_form(&$form, &$form_state, $tag) {
  $form['rtc_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Real Time Configuration'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );

  // Vendors & Macros (rtc_vendor_helper.inc).
  module_load_include('inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_vendors');
  _amp_dfp_rtc_build_vendors($form, $form_state, $tag);

  // Urls  (rtc_url_helper.inc).
  module_load_include('inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_urls');
  _amp_dfp_rtc_build_urls($form, $form_state, $tag);

  // Timeout.
  module_load_include('inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_timeout');
  _amp_dfp_rtc_build_timeout($form, $form_state, $tag);

  //So the submit handler runs before $tag->settings is saved.
  array_unshift($form['#submit'], '_amp_dfp_rtc_config_submit');
}

/**
 * todo
 *
 * @param $form
 * @param $form_state
 */
function _amp_dfp_rtc_config_submit(&$form, &$form_state) {
  $rtc_config['vendor'] = $form_state['input']['rtc_config']['wrapper']['vendor'];
  $rtc_config['urls'] = $form_state['input']['rtc_config']['urls']['url_wrapper'];
  $rtc_config['timeout'] = $form_state['input']['rtc_config']['timeout'];
  $form_state['values']['settings']['rtc_config'] = $rtc_config;
}
