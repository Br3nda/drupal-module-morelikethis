<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.admin.inc,v 1.1.2.2 2008/10/24 20:49:01 febbraro Exp $
 */
/**
 * @file morelikethis.admin.inc
 */

/**
 * Settings for More Like This functionality.
 */
function morelikethis_settings() {

  drupal_set_title('More Like This Configuration Settings');
  $form = array();
  
  // Allow prepoulating by relevance if calais exists
  if(module_exists('calais')) {
    $form['morelikethis_calais_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pre-populate with Calais Suggestions'),
      '#default_value' => variable_get("morelikethis_calais_default", FALSE),
      '#description' => t('If enabled the More Like This terms will get prepopulated from the Calais suggestions according to the threshold specified below.'),
    );
    $form["morelikethis_calais_relevance"] = array(
      '#type' => 'textfield',
      '#size' => 6,
      '#maxlength' => 6,
      '#title' => t('Relevance Threshold'),
      '#default_value' => variable_get("morelikethis_calais_relevance", '0.500'),
      '#description' => t('The relevance threshold for More Like This default terms. Only Calais suggestions with a relevance score <em>greater</em> than or equal to this threshold will be matched. This threshold is specified as a value between 0.000 and 1.000, with 1 being the most relevant.'),
    );
    $form = system_settings_form($form);
  }
  else {
    // Do this only if there are no settings to displau (b/c Calais is not enabled)
    $services = _morelikethis_providers();
    foreach ($services as $key=> $service) {
      if(isset($service['#settings'])) {
        $url = l($service['#title'], "admin/settings/morelikethis/$key");
        if(!empty($service['#description'])) {
          $url .= '<br/>' . $service['#description'];
        }
        $items[] = $url;
      }
    }

    $form['title'] = array(
      '#value' => t('More Like This Configuration Settings'),
      '#prefix' => '<h2>',
      '#suffix' => '</h2>',    
    );
    $form['links'] = array(
      '#value' => theme('item_list', $items),
    );    
  }
  return $form;
}
