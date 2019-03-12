<?php

/**
 * @file
 * Real time configuration helper file to break out the form components.
 * This file deals with the timeout element of the form.
 */

/**
 * Function to build the timeout section of the form.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The current form state.
 * @param mixed $tag
 *   The dfp tag.
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
