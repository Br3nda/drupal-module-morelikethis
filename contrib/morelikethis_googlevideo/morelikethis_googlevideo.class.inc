<?php
/**
 * @file morelikethis_googlevideo.class.inc
 * 
 * For Google Video, the results of an API search are handled via javascript.  That means there are no
 * "items" for find to return.  This class is only needed so Google Video will fit the framework
 * of the MoreLikeThis module.
 * 
 */
class MoreLikeThisGoogleVideo extends MoreLikeThisBase {

  public function isEnabled($type) {
    $key = drupal_strtolower($type);
    return variable_get("morelikethis_gv_content_type_$key", FALSE);
  }
    
  public function find($settings = array()) {
    return array();    
  }
}