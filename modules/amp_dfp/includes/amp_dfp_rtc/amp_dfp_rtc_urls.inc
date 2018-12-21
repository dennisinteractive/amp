<?php

/**
 * @file
 * Real time configuration helper file to break out the form components.
 * This file deals with the url element of the form.
 */

/**
 * Function to build the urls section of the form.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The current form state.
 * @param mixed $tag
 *   The dfp tag.
 */
function _amp_dfp_rtc_build_urls(&$form, &$form_state, $tag) {
  $form['rtc_config']['urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Urls'),
    '#collapsible' => TRUE,
    '#description' => t('Url configuration, if an error reporting url is present, both fields must be populated.'),
  );

  if (empty($form_state['num_urls'])) {
    $form_state['num_urls'] = 1;
  }

  $form['rtc_config']['urls']['url_wrapper'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="rtc-url-wrapper">',
    '#sufix' => '</div>',
    '#theme' => 'rtc_url_settings',
  );

  if (isset($tag->settings['rtc_config']['urls']) && count($tag->settings['rtc_config']['urls']) > $form_state['num_urls']) {
    $form_state['num_urls'] = count($tag->settings['rtc_config']['urls']);
  }

  for ($k = 0; $k < $form_state['num_urls']; $k++) {
    $form['rtc_config']['urls']['url_wrapper'][$k]['rtc_url'] = array(
      '#type' => 'textfield',
      '#description' => empty($tag->settings['rtc_config']['urls'][$k]['rtc_url']) ? 'must be in the format: https://www.example.com' : '',
      '#value' => isset($tag->settings['rtc_config']['urls'][$k]['rtc_url']) ? $tag->settings['rtc_config']['urls'][$k]['rtc_url'] : '',
    );

    $form['rtc_config']['urls']['url_wrapper'][$k]['rtc_error_url'] = array(
      '#type' => 'textfield',
      '#value' => isset($tag->settings['rtc_config']['urls'][$k]['rtc_error_url']) ? $tag->settings['rtc_config']['urls'][$k]['rtc_error_url'] : '',
    );
  }
  $form['rtc_config']['url_button'] = array(
    '#type' => 'markup',
    '#tree' => TRUE,
    '#prefix' => '<div id="rtc-url-button">',
    '#suffix' => '</div>',
    '#parents' => array('rtc_config', 'urls'),
  );
  $form['rtc_config']['url_button']['more_rtc_url'] = array(
    '#type' => 'submit',
    '#value' => t('Add url'),
    '#submit' => array('_amp_dfp_rtc_urls_form_submit'),
    '#ajax' => array(
      'callback' => '_amp_dfp_rtc_urls_form_elements_callback',
      'wrapper' => 'rtc-url-wrapper',
      'effect' => 'fade',
    ),
  );
}

/**
 * Theme function for the "url" form.
 *
 * @param mixed $variables
 *   Drupal variables.
 */
function theme_rtc_url_settings($variables) {
  $form = $variables['form'];
  $headers = array(t('Url'), t('Error reporting url (optional)'));
  $rows = array();

  foreach (element_children($form) as $key) {
    if (is_numeric($key) && !empty($form[$key]['rtc_url'])) {
      $rows[] = array(
        drupal_render($form[$key]['rtc_url']),
        drupal_render($form[$key]['rtc_error_url']),
      );
    }
  }

  return theme('table', array('header' => $headers, 'rows' => $rows));
}

/**
 * Ajax Submit handler to add another url.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The current form state.
 */
function _amp_dfp_rtc_urls_form_submit(&$form, &$form_state) {
  $form_state['rtc_config'] = $form_state['input']['rtc_config'];
  $form_state['num_urls']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Ajax callback to add another url.
 *
 * @param mixed $form
 *   The form.
 * @param mixed $form_state
 *   The form state.
 *
 * @return mixed
 *   The complete url table element.
 */
function _amp_dfp_rtc_urls_form_elements_callback(&$form, &$form_state) {
  // Load in previous urls.
  $urls = count($form['rtc_config']['wrapper']['vendor'][$form_state['input']['vendor_key']]['macros']);
  for ($i = 0; $i < $urls; $i++) {
    if (isset($form_state['input']['rtc_config']['urls']['url_wrapper'][$i]['rtc_url']) && !empty($form_state['input']['rtc_config']['urls']['url_wrapper'][$i]['rtc_url'])) {
      $form['rtc_config']['urls']['url_wrapper'][$i]['rtc_url']['#value'] = $form_state['input']['rtc_config']['urls']['url_wrapper'][$i]['rtc_url'];
      $form['rtc_config']['urls']['url_wrapper'][$i]['rtc_error_url']['#value'] = $form_state['input']['rtc_config']['urls']['url_wrapper'][$i]['rtc_error_url'];
    }
  }

  return $form['rtc_config']['urls']['url_wrapper'];
}
