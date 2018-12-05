<?php

include 'helpers/rtc_vendor_helper.inc';
include 'helpers/rtc_url_helper.inc';

function _amp_rtc_configuration_form(&$form, &$form_state, $tag) {
  $form['rtc_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Real Time Configuration'),
    '#tree' => TRUE,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );

  //Vendors & Macros (rtc_vendor_helper.inc)
  _amp_rtc_build_vendors($form, $form_state, $tag);
  //Urls  (rtc_url_helper.inc)
  _amp_rtc_build_urls($form, $form_state, $tag);
  //Timeout
  _amp_rtc_build_timeout($form, $form_state, $tag);

  //So the submit handler runs before $tag->settings is saved.
  array_unshift($form['#submit'], '_amp_rtc_config_submit');
}

function _amp_rtc_build_timeout(&$form, &$form_state, $tag) {
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

function _amp_rtc_config_submit(&$form, &$form_state) {
  $rtc_config['vendor'] = $form_state['input']['rtc_config']['wrapper']['vendor'];
  $rtc_config['urls'] = $form_state['input']['rtc_config']['urls']['url_wrapper'];
  $rtc_config['timeout'] = $form_state['input']['rtc_config']['timeout'];
  $form_state['values']['settings']['rtc_config'] = $rtc_config;
}
