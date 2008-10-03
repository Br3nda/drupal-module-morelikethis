<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.admin.inc,v 1.1 2008/10/03 16:36:58 febbraro Exp $
 */
/**
 * @file morelikethis.admin.inc
 */

/**
 * Settings for More Like This functionality.
 */
function morelikethis_settings_form() {
  
  node_types_rebuild();
  $types = node_get_types('types', NULL, TRUE);
  
  $options = array();
  foreach ($types as $type) {
    $options[$type->type] = $type->name;
  }
  
  $form = array();
  foreach ($types as $type) {
    $key = drupal_strtolower($type->type);
    $name = $type->name;
    $param_name = array('@name' => $name);
    
    $form["morelikethis_{$key}"] = array(
      '#type' => 'fieldset',
      '#title' => t('@name', $param_name),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form["morelikethis_{$key}"]["morelikethis_enabled_{$key}"] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable More Like This'),
      '#default_value' => variable_get("morelikethis_enabled_{$key}", FALSE),
      '#description' => t('Should searches for more content like this be enabled for this content type.'),
    );
    $form["morelikethis_{$key}"]["morelikethis_target_types_{$key}"] = array(
      '#type' => 'select',
      '#title' => t('Target Content Types'),
      '#default_value' => variable_get("morelikethis_target_types_{$key}", NULL),
      '#options' => $options,
      '#multiple' => TRUE,
      '#size' => 4,
      '#description' => t('Select which type of site content types you would like returned in more like this searches for @name. You can select multiple types by ctrl+click or apple+click.', $param_name),
    );
    $form["morelikethis_{$key}"]["morelikethis_count_{$key}"] = array(
      '#type' => 'textfield',
      '#title' => t('Number of results'),
      '#size' => 4,
      '#maxlength' => 4,
      '#default_value' => variable_get("morelikethis_count_{$key}", NULL),
      '#description' => t('Specify the number of items to include in the listing of More Like This results. Default: 10'),
    );
    $form["morelikethis_{$key}"]["morelikethis_threshold_{$key}"] = array(
      '#type' => 'textfield',
      '#size' => 6,
      '#maxlength' => 6,
      '#title' => t('Threshold'),
      '#default_value' => variable_get("morelikethis_threshold_{$key}", NULL),
      '#description' => t('The relevancy threshold for More Like This association. Only items with a threshold score <em>greater</em> than or equal to this threshold will be matched. The threshold score is a percentage of terms that match. Specify the threshold in the range 0.0 - 1.0 (If 2 of 3 terms match, the threshold score is 0.667. 1 of 4 terms match is 0.25). Default: 0.0'),
    );
  }
    
  return system_settings_form($form);
}