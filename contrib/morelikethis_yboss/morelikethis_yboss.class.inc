<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis_yboss.class.inc,v 1.1.2.5 2008/12/19 22:08:36 febbraro Exp $
*/
/**
 * @file morelikethis_yboss.class.inc
 */

abstract class YahooBossBase extends MoreLikeThisBase {
  
  /**
   * Get a setting for a specific content type. If the setting is not set,
   * fall back to a global setting.
   */
  protected function getSetting($type, $key, $default = '') {
    $var = variable_get("{$key}_{$type}", $default);
    return (isset($var) && $var != '') ? $var : variable_get($key, $default);
  }  
  
  protected function searchYboss($keys = '', $query = array(), $search = 'web', $version = 'v1') {
    $defaults = array(
      'lang' => variable_get('morelikethis_yboss_lang', 'en'),
      'appid' => variable_get('morelikethis_yboss_appid', ''),
      'format' => 'xml',
      'region' => variable_get('morelikethis_yboss_region', 'us'),
    );
    $query = array_merge($defaults, $query);
    
    $uri = 'http://boss.yahooapis.com/ysearch/' . $search . '/' . $version . '/' . drupal_urlencode($keys);
    $uri .= '?' . drupal_query_string_encode($query);
    $request = drupal_http_request($uri);
    
    if ($query['format'] == 'xml') {
      $response = simplexml_load_string($request->data);
      
      if(!$response) {
        return array();
      }
      
      $search = 'resultset_' . $search;
      $attributes = isset($response->$search) ? $response->$search->attributes() : array();
      if ($error = $response->children('http://schemas.yahooapis.com/'. $version .'/schema.xsd')) {
        drupal_set_message(t('Yahoo BOSS error: @description (@detail).', array('@description' => $error->description, '@detail' => $error->detail)), 'error');
      }   
      $items = array();
      foreach ($response->$search->result as $result) {
        $items[] = $result;
      }
      return $items;
    }

    return $request->data;
  }
}

/**
 * Execute a web or news query on the Yahoo! BOSS Web Service.
 */
class MoreLikeThisYahooBoss extends YahooBossBase {
  
  public function isEnabled($type) {
    $key = drupal_strtolower($type);
    return variable_get("morelikethis_yboss_enabled_{$key}", FALSE);
  }
  
  public function find($settings = array()) {
    $term_count = count($this->terms);
    if($term_count == 0)
      return FALSE;

    $type = drupal_strtolower($this->node->type);
    $search = variable_get("morelikethis_yboss_search_{$type}", 'web');
    $count = variable_get("morelikethis_yboss_count_{$type}", '10');
    $yb_query = variable_get("morelikethis_yboss_query", NULL);

    $query = array(
      'count' => $count,
      'type' => $this->getSetting($type, 'morelikethis_yboss_type'),
    );
    
    // Add the terms here, surrounded by quotes
    $key_terms = array();
    foreach($this->terms as $term) {
      $key_terms[] = '"' . $term . '"';
    }
    $keys = implode($key_terms, ' ');
    $keys .= $yb_query ? ' ' . $yb_query : '';

    $results = $this->searchYboss($keys, $query, $search);

    $items = array();
    foreach ($results as $result) {
      $builder = "{$search}BuildClass";
      $item = $this->$builder($result);
      $item->mlt_type = 'yboss';
      $item->yboss_type = $search;
      $items[] = $item;
    }
    return $items;
  }
  
  protected function webBuildClass($result) {
    $item = new stdClass;
    $item->id = $result->url;
    $item->title = strip_tags($result->title);
    $item->teaser = $result->abstract;
    $item->date = $result->date;
    $item->url = $result->url;
    $item->clickurl = $result->clickurl;
    return $item;
  }

  protected function newsBuildClass($result) {
    $item = $this->webBuildClass($result);
    $item->source = $result->source;
    $item->sourceurl = $result->sourceurl;
    return $item;
  }
}

/**
 * Execute an images query on the Yahoo! BOSS Web Service.
 */
class MoreLikeThisYahooBossImages extends YahooBossBase {
  
  public function isEnabled($type) {
    $key = drupal_strtolower($type);
    return variable_get("morelikethis_ybossimg_enabled_{$key}", FALSE);
  }
  
  public function find($settings = array()) {
    $term_count = count($this->terms);
    if($term_count == 0)
      return FALSE;

    $type = drupal_strtolower($this->node->type);
    $count = variable_get("morelikethis_ybossimg_count_{$type}", '10');
    $yb_query = $this->getSetting($type, 'morelikethis_ybossimg_query', NULL);

    $query = array(
      'count' => $count,
      'filter' => $this->getSetting($type, 'morelikethis_ybossimg_filter'),
      'dimensions' => $this->getSetting($type, 'morelikethis_ybossimg_dimensions'),
    );
    
    // Yahoo Boss can't search on more than one term, so pick the first term.
    $keys = '"' . $this->terms[0] . '"';
    $keys .= $yb_query ? ' ' . $yb_query : '';

    $results = $this->searchYboss($keys, $query, 'images');
    foreach ($results as $result) {
      $item = new stdClass;
      $item->id = $result->url;
      $item->title = strip_tags($result->title);
      $item->teaser = $result->abstract;
      $item->date = $result->date;
      $item->url = $result->url;
      $item->clickurl = $result->clickurl;
      $item->filename = $result->filename;
      $item->format = $result->format;
      $item->width = $result->width;
      $item->height = $result->height;
      $item->mimetype = $result->mimetype;
      $item->refererurl = $result->refererurl;
      $item->refererclickurl = $result->refererclickurl;
      $item->thumbnail_url = $result->thumbnail_url;
      $item->thumbnail_width = $result->thumbnail_width;
      $item->thumbnail_height = $result->thumbnail_height;
      $item->mlt_type = 'ybossimg';
      $item->yboss_type = 'images';
      $items[] = $item;
    }
    return $items;
  }
}

