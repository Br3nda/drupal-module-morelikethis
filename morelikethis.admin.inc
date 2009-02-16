<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.admin.inc,v 1.1.2.6 2009/02/16 21:53:45 emackn Exp $
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
  $form['main_description'] = array(
    '#prefix' => "<h4>",
    '#suffix' => "</h4>",
    '#value'=> t("These are global settings for More Like This (MLT).  MLT terms are used to retrieve various types of related content, and are generally a subset of the larger pool of Calais tags.  However, in some instances you might want to apply an additional MLT term that was not suggested by Calais."),
  );
  // Allow prepoulating by relevance if calais exists
  if(module_exists('calais')) {
    $form['morelikethis_calais_default'] = array(
      '#type' => 'checkbox',
      '#title' => t('Pre-populate with Calais Suggestions'),
      '#default_value' => variable_get("morelikethis_calais_default", FALSE),
      '#description' => t("Provides the ability to pre-fill applied MLT terms using eligible Calais terms by simply checking a box on a node's edit page (relevancy threshold below determines eligibility)."),
    );
    $form["morelikethis_calais_relevance"] = array(
      '#type' => 'textfield',
      '#size' => 6,
      '#maxlength' => 6,
      '#title' => t('Global Term Relevancy Threshold for MLT'),
      '#default_value' => variable_get("morelikethis_calais_relevance", MORELIKETHIS_DEFAULT_RELEVANCE),
      '#description' => t('Determine how relevant a Calais term must be in order to be considered a "candidate" for inclusion as an applied MLT term. Uses a 0.00-1.00 scale, 0.00 being least relevant (i.e. all Calais terms will be candidates for applied MLT terms). '),
    );
    $form = system_settings_form($form);
  }
  else {
    // Do this only if there are no settings to display (b/c Calais is not enabled)
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
