<?php

function _amp_rtc_configuration_form(&$form, &$form_state, $tag) {
  
  $form['#tree'] = TRUE;
  
  $form['rtc_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('RTC configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'settings',
  );

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
      '#description' => t('RTC vendor configuration.'),
      '#parents' => array('rtc_config', 'wrapper', 'vendor'),
    );

    $form['rtc_config']['wrapper']['vendor'][$i]['vendor_name'] = array(
      '#type' => 'textfield',
      '#title' => t('Vendor name'),
      '#description' => t('RTC vendor name.'),
      '#parents' => array('rtc_config', 'wrapper', 'vendor', $i, 'vendor_name'),
      '#value' => isset($tag->settings['rtc_config']['vendor'][$i]['vendor_name']) ? $tag->settings['rtc_config']['vendor'][$i]['vendor_name'] : '',
    );

    $form['rtc_config']['wrapper']['vendor'][$i]['vendor_key'] = array(
      '#type' => 'hidden',
      '#value' => $i,
      '#name' => 'vendor_key'
    );

    $form['rtc_config']['wrapper']['vendor'][$i]['macros'] = array(
      '#type' => 'markup',
      '#tree' => FALSE,
      '#prefix' => '<div id="rtc-macro-table-' . $i . '">',
      '#suffix' => '</div>',
      '#theme' => 'rtc_macro_settings',
      '#parents' => array('rtc_config', 'wrapper', 'vendor', $i, 'macros'),
    );

    if (isset($tag->settings['rtc_config']['vendor'][$i]['macros']) && count($tag->settings['rtc_config']['vendor'][$i]['macros']) > $form_state['num_macros'][$i]) {
      $form_state['num_macros'][$i] = count($tag->settings['rtc_config']['vendor'][$i]['macros']);
    }
    
    for ($j = 0; $j < $form_state['num_macros'][$i]; $j++) {
      $form['rtc_config']['wrapper']['vendor'][$i]['macros'][$j]['macro'] = array(
        '#type' => 'textfield',
        '#value' => isset($tag->settings['rtc_config']['vendor'][$i]['macros'][$j]['macro']) ? $tag->settings['rtc_config']['vendor'][$i]['macros'][$j]['macro'] : '',
        '#parents' => array('rtc_config', 'wrapper', 'vendor', $i, 'macros', $j, 'macro'),
      );
      $form['rtc_config']['wrapper']['vendor'][$i]['macros'][$j]['value'] = array(
        '#type' => 'textfield',
        '#value' => isset($tag->settings['rtc_config']['vendor'][$i]['macros'][$j]['value']) ? $tag->settings['rtc_config']['vendor'][$i]['macros'][$j]['value'] : '',
        '#parents' => array('rtc_config', 'wrapper', 'vendor', $i, 'macros', $j, 'value'),
      );
    }

    $form['rtc_config']['wrapper']['vendor'][$i]['more_macro'] = array(
      '#type' => 'submit',
      '#value' => t('Add vendor macro'),
      '#submit' => array('_amp_rtc_macro_form_submit'),
      '#parents' => array('rtc_config', 'wrapper', 'vendor', $i),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => '_amp_rtc_macro_form_elements_callback',
        'wrapper' => 'rtc-macro-table-' . $i,
        'effect' => 'fade',
      ),
    );
  }

  $form['rtc_config']['urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Urls'),
    '#collapsible' => TRUE,
    '#description' => t('RTC url configuration.'),
  );

  if (empty($form_state['num_urls'])) {
    $form_state['num_urls'] = 1;
  }

  $form['rtc_config']['urls']['url_wrapper'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="rtc-url-wrapper">',
    '#sufix' => '</div>',
    '#theme' => 'rtc_url_settings'
  );

  if (isset($tag->settings['rtc_config']['urls']) && count($tag->settings['rtc_config']['urls']) > $form_state['num_urls']) {
    $form_state['num_urls'] = count($tag->settings['rtc_config']['urls']);
  }

  for ($k = 0; $k < $form_state['num_urls']; $k++) {
    $form['rtc_config']['urls']['url_wrapper'][$k]['rtc_url'] = array(
      '#type' => 'textfield',
      '#value' => isset($tag->settings['rtc_config']['urls'][$k]['rtc_url']) ? $tag->settings['rtc_config']['urls'][$k]['rtc_url'] : '',
    );

    $form['rtc_config']['urls']['url_wrapper'][$k]['rtc_error_url'] = array(
      '#type' => 'textfield',
      '#value' => isset($tag->settings['rtc_config']['urls'][$k]['rtc_error_url']) ? $tag->settings['rtc_config']['urls'][$k]['rtc_error_url'] : '',
    );
  }

  $form['rtc_config']['wrapper_timeout'] = array(
    '#type' => 'fieldset',
    '#title' => t('Timeout configuration'),
    '#collapsible' => TRUE,
    '#description' => t('RTC timeout configuration.'),
    '#parents' => array('rtc_config'),
  );

  $form['rtc_config']['wrapper_timeout']['timeoutMillis'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout'),
    '#description' => t('RTC timeout configuration (in milliseconds).'),
    '#value' => isset($tag->settings['rtc_config']['timeoutMillis']) ? $tag->settings['rtc_config']['timeoutMillis'] : 6000,
  );

  $form['rtc_config']['button_wrapper'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="button-wrapper">',
    '#suffix' => '</div>',
  );

  $form['rtc_config']['button_wrapper']['more_rtc_vendors'] = array(
    '#type' => 'submit',
    '#value' => t('Add vendor'),
    '#submit' => array('_amp_rtc_vendor_form_submit'),
    '#parents' => array('rtc_config'),
    '#suffix' => '&nbsp;',
    '#ajax' => array(
      'callback' => '_amp_rtc_vendor_form_elements_callback',
      'wrapper' => 'rtc-vendor-wrapper',
      'effect' => 'fade',
      'method' => 'append',
    ),
  );
  $form['rtc_config']['button_wrapper']['more_rtc_url'] = array(
    '#type' => 'submit',
    '#value' => t('Add url'),
    '#submit' => array('_amp_rtc_urls_form_submit'),
    '#ajax' => array(
      'callback' => '_amp_rtc_urls_form_elements_callback',
      'wrapper' => 'rtc-url-wrapper',
      'effect' => 'fade',
    ),
  );
  $form['#validate'][] = '_amp_rtc_config_validate';

  array_unshift($form['#submit'], '_amp_rtc_config_submit');
}

/**
 * Theme function for the "macro" form.
 */
function theme_rtc_macro_settings($variables) {
  $form = $variables['form'];
  //dpm($form);
  $headers = array(t('Macro'), t('Value'));
  $rows = array();
  foreach (element_children($form) as $key) {

    if (is_numeric($key) && !empty($form[$key]['macro'])) {
      $rows[] = array(drupal_render($form[$key]['macro']), drupal_render($form[$key]['value']));
    }
  }
  return theme('table', array('header' => $headers, 'rows' => $rows)); // . $more_button;
}

/**
 * Theme function for the "url" form.
 */
function theme_rtc_url_settings($variables) {
  $form = $variables['form'];
  $headers = array(t('Url'), t('Error reporting url (optional)'));
  $rows = array();
  foreach (element_children($form) as $key) {
    if (is_numeric($key) && !empty($form[$key]['rtc_url'])) {
      $rows[] = array(drupal_render($form[$key]['rtc_url']), drupal_render($form[$key]['rtc_error_url']));
    }
  }
  return theme('table', array('header' => $headers, 'rows' => $rows));
}

function _amp_rtc_vendor_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['values']['rtc_config'];
  $form_state['num_vendors'] ++;

  $form_state['rebuild'] = TRUE;
}

function _amp_rtc_vendor_form_elements_callback(&$form, &$form_state) {
  return $form['rtc_config']['wrapper']['vendor'];
}

function _amp_rtc_config_validate(&$form, &$form_state) {
  $vendors = $form_state['input']['rtc_config']['wrapper']['vendor'];
  $urls = $form_state['input']['rtc_config']['urls']['url_wrapper'];
  for ($i = 0; $i < count($vendors); $i++) {

    if (!empty($vendors[$i]['macro'])) {
      if (empty($vendors[$i]['vendor_name'])) {
        form_set_error('vendor_name', 'Vendor cannot be empty.');
      }
      for ($j = 0; $j < count($vendors[$i]['macro']); $j++) {
        if (empty($vendors[$i]['macro'][$j]['macro'])) {
          form_set_error('macro', 'Macro cannot be empty.');
        }
        if (empty($vendors[$i]['macro'][$j]['value'])) {
          form_set_error('value', 'Macro value cannot be empty.');
        }
      }
    }
  }
  for ($i = 0; $i < count($urls); $i++) {
    if (!empty($urls[$i]['rtc_error_url'])) {
      if (empty($urls[$i]['rtc_url'])) {
        form_set_error('value', 'Macro value cannot be empty.');
      }
    }
  }
}

function _amp_rtc_macro_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['input']['rtc_config'];
  $form_state['num_macros'][$form_state['input']['vendor_key']] ++;
  $form_state['rebuild'] = TRUE;
}

function _amp_rtc_macro_form_elements_callback(&$form, &$form_state) {
  return $form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros'];
}

function _amp_rtc_urls_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['input']['rtc_config'];
  $form_state['num_urls'] ++;
  $form_state['rebuild'] = TRUE;
}

function _amp_rtc_urls_form_elements_callback(&$form, &$form_state) {
  return $form['rtc_config']['urls']['url_wrapper'];
}

function _amp_rtc_config_submit(&$form, &$form_state) {
  $rtc_config['vendor'] = $form_state['input']['rtc_config']['wrapper']['vendor'];
  $rtc_config['urls'] = $form_state['input']['rtc_config']['urls']['url_wrapper'];
  $rtc_config['timeoutMillis'] = $form_state['input']['rtc_config']['timeoutMillis'];
  $form_state['values']['settings']['rtc_config'] = $rtc_config;
}
