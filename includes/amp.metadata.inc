<?php

/**
 * @file
 * AMP Metadata.
 */

/**
 * Adds ld+json metadata to the page.
 *
 * @param array $metadata_json
 */
function amp_metadata($metadata_json = array()) {
  // Add global publisher info.
  $metadata_json['publisher'] = array(
    '@type' => 'Organization',
    'name' => variable_get('amp_metadata_organization_name', ''),
  );

  $logo_fid = variable_get('amp_metadata_organization_logo', NULL);
  if ($logo_fid) {
    $logo = file_load($logo_fid);
    $logo_uri = $logo->uri;
    $logo_url = file_create_url($logo_uri);
    if (!empty($logo_url) && !empty($logo_uri)) {
      $logo_style_id = variable_get('amp_metadata_organization_logo_image_style_id', '');
      if (!empty($logo_info = _amp_get_image_information($logo_url, $logo_uri, $logo_style_id))) {
        $metadata_json['publisher']['logo'] = array(
          '@type' => 'ImageObject',
          'url' => $logo_info['url'],
          'width' => $logo_info['width'],
          'height' => $logo_info['height'],
        );
      }
    }
  }

  drupal_alter('amp_metadata', $metadata_json, $node, $type);

  // Replace the tokens.
  array_walk_recursive($metadata_json, function(&$value) use ($node) {
    $value = strip_tags(token_replace($value));
    $value = str_replace("\n", "", $value);
    $value = str_replace("\r", "", $value);
  });

  $element = array(
    '#tag' => 'script',
    '#type' => 'html_tag',
    '#attributes' => array(
      'type' => 'application/ld+json',
    ),
    '#value' => json_encode($metadata_json, JSON_PRETTY_PRINT | JSON_UNESCAPED_SLASHES | JSON_HEX_TAG | JSON_HEX_APOS | JSON_HEX_AMP | JSON_HEX_QUOT), array('node' => $node),
  );

  drupal_add_html_head($element, 'amp_metadata');
}

/**
 * Implements hook_form_FORM_ID_alter().
 */
function amp_form_node_type_form_alter(&$form, &$form_state, $form_id) {
  $enabled_types = amp_get_enabled_types();
  if (in_array($form['#node_type']->type, $enabled_types)) {
    $form['amp_metadata'] = array(
      '#type' => 'fieldset',
      '#title' => t('AMP Metadata'),
      '#group' => 'additional_settings',
      '#weight' => 100,
    );

    $form['amp_metadata']['description'] = array(
      '#type' => 'item',
      '#title' => 'Content information',
      '#description' => t('Provide information about your content for use in the Top Stories carousel in Google Search.'),
    );


    $form['amp_metadata']['amp_metadata_options'] = array(
      '#type' => 'container',
      '#tree' => 'true',
    );

    $amp_metadata_fields = _amp_get_metadata_type_fields();

    $settings = variable_get('amp_metadata_options_' . $form['#node_type']->type);

    foreach ($amp_metadata_fields as $name => $field) {
      $form_options['amp_metadata_config_' . $name] = array(
        '#type' => 'textfield',
        '#title' => t('@title', array('@title' => ucfirst($name))),
        '#default_value' => isset($settings['amp_metadata_config_' . $name]) ? $settings['amp_metadata_config_' . $name] : $field['value'],
      );
      switch ($name) {
        case 'schemaType':
          $schema_type_options = array(
            'Article' => 'Article',
            'NewsArticle' => 'NewsArticle',
            'BlogPosting' => 'BlogPosting',
          );
          $form_options['amp_metadata_config_' . $name]['#title'] = 'AMP schema type';
          $form_options['amp_metadata_config_' . $name]['#type'] = 'select';
          $form_options['amp_metadata_config_' . $name]['#options'] = $schema_type_options;
          $form_options['amp_metadata_config_' . $name]['#description'] = t('The type of schema to use on AMP pages');
          break;
        case 'headline':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Article headline';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>A short headline for an AMP article, using fewer than 110 characters and no HTML markup.</p>
          <p>Use tokens to provide the correct headline for each article page. Suggested token: [node:title].'
          );
          $form_options['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:title]'];
          break;
        case 'datePublished':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Date published';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>The date an article was published.</p>
          <p>Use tokens to provide the correct published date for each article. Suggested token: [node:created].'
          );
          $form_options['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:created]'];
          break;
        case 'dateModified':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Date modified';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>The date an article was most recently modified date.</p>
          <p>Use tokens to provide the correct modification date for each article. Suggested token: [node:changed].'
          );
          $form_options['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:changed]'];
          break;
        case 'author':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Author';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>The name of the author to use on AMP pages.</p>
          <p>Use tokens to provide the correct author for each article. Token output should be text only, no HTML markup. Suggested token: [node:author:name].'
          );
          $form['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:author:name]'];
          break;
        case 'description':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Article description';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>A short description of an AMP article, using fewer than 150 characters and no HTML markup.</p>
          <p>Use tokens to provide the correct description for each article. Suggested token: [node:summary].'
          );
          $form_options['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:summary]'];
          break;
        case 'image':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Article image for carousel';
          $form_options['amp_metadata_config_' . $name]['#description'] = t('
          <p>An article image to appear in the Top Stories carousel.</p>
          <p>Images must be at least 696px wide: refer to <a href="@image_guidelines">article image guidelines</a> for further details.</p>
          <p>Use tokens to provide the correct image for each article. Example token: [node:field_image]. The image field token likely varies by content type.',
            array('@image_guidelines' => 'https://developers.google.com/search/docs/data-types/articles#article_types')
          );
          $form_options['amp_metadata_config_' . $name]['#attributes'] = ['placeholder' => '[node:field_image]'];
          break;
        case 'imageStyle':
          $form_options['amp_metadata_config_' . $name]['#title'] = 'Article image style';
          $form_options['amp_metadata_config_' . $name]['#type'] = 'select';
          $form_options['amp_metadata_config_' . $name]['#options'] = image_style_options(TRUE);
          $form_options['amp_metadata_config_' . $name]['#description'] = t('<p>The image style to use for the article image</p>');
          break;
      }
    }

    $form['amp_metadata']['amp_metadata_options'] += $form_options;

    $form['amp_metadata']['amp_metadata_token_tree'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('node'),
      '#dialog' => TRUE,
    );

    $form['#submit'][] = 'amp_metadata_node_type_submit';
  }
}

/**
 * Additional submit handler for the node type form.
 */
function amp_metadata_node_type_submit(&$form, $form_state) {
  variable_set('amp_metadata_options_' . $form['#node_type']->type, $form_state['values']['amp_metadata_options']);
}
