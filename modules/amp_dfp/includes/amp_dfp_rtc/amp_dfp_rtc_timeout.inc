<?php
/**
 * @file real time configuration helper file to break out the form components, this file deals
 * with the timeout element of the form.
 *
 */

/**
 * function to build the timeout section of the form.
 *
 * @param $form
 * @param $form_state
 * @param $tag
 */
function _amp_dfp_rtc_build_timeout(&$form, &$form_state, $tag) {
  $form['rtc_config']['wrapper_timeout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Timeout configuration'),
    '#collapsible' => TRUE,
    '#description' => t('Timeout value is in milliseconds, (60 seconds = 6000 milliseconds'),
    '#parents' => array('rtc_config'),
  );

  $form['rtc_config']['wrapper_timeout']['timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('RTC timeout configuration (in milliseconds).'),
    '#value' => isset($tag->settings['rtc_config']['timeout']) ? $tag->settings['rtc_config']['timeout'] : '',
  );
}
