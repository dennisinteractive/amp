<?php
/**
 * @file Main file for providing real time configuration functionality for amp-ad elements
 */

/**
 * RTC form to pull in the main elements of the rtc form.
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

  // Vendors & Macros (amp_dfp_rtc_vendor.inc).
  form_load_include($form_state, 'inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_vendors');
  _amp_dfp_rtc_build_vendors($form, $form_state, $tag);

  // Urls  (amp_dfp_rtc_url.inc).
  form_load_include($form_state, 'inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_urls');
  _amp_dfp_rtc_build_urls($form, $form_state, $tag);

  // Timeout (amp_dfp_rtc_timeout.inc).
  form_load_include($form_state, 'inc', 'amp_dfp', 'includes/amp_dfp_rtc/amp_dfp_rtc_timeout');
  _amp_dfp_rtc_build_timeout($form, $form_state, $tag);

  // So the submit handler runs before $tag->settings is saved.
  array_unshift($form['#submit'], '_amp_dfp_rtc_config_submit');
}

/**
 * Submit handler for the rtc elements of the form.
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
