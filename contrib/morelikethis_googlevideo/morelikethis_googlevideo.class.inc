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
    $path = drupal_get_path('module', 'morelikethis_googlevideo');
    drupal_add_js($path . "/api.js");
    drupal_add_css($path .'/gsearch.css');
    drupal_add_js($path .'/gsvideobar.js');  
    drupal_add_css($path .'/gsvideobar.css');
  
    $tags = implode('", "', $this->terms);
    $tags = '"'.$tags.'"';
  
	  $status_bar = variable_get('morelikethis_gv_use_statusroot', TRUE);
	  $status_root = ($status_bar ? 'statusRoot : document.getElementById("'.
	   variable_get('medialikethis_gv_statusroot_id', 'videoBarStatus').'"),' : '');
	   
	  drupal_add_js('
	    function LoadVideoBar() {
	      var vbr;
	      
	      var options = {
	        largeResultSet : '.variable_get('morelikethis_gv_large_result_set', 'false').',
	        horizontal : '.variable_get('morelikethis_gv_orient', 'true').',
	        autoExecuteList : {
	          cycleTime : '.variable_get('morelikethis_gv_cycle_time', 'GSvideoBar.CYCLE_TIME_SHORT').',
	          cycleMode : '.variable_get('morelikethis_gv_cycle_mode', 'GSvideoBar.CYCLE_MODE_LINEAR').','. 
	          $status_root .    
	         'executeList : ['.$tags.']
	        }
	      }
	      
	      vbr = new GSvideoBar(
	                  document.getElementById("'.variable_get('morelikethis_gv_videobar_id', 'google_video_like_this_bar').'"),
	                  GSvideoBar.PLAYER_ROOT_FLOATING,
	                  options
	                  );
	    }
	    
	    GSearch.setOnLoadCallback(LoadVideoBar);  
	    ', 'inline');
       
    $item['video_bar_id'] = variable_get('morelikethis_gv_videobar_id', 'google_video_like_this_bar'); 
    $item['status_bar_id'] = variable_get('morelikethis_gv_statusroot_id', 'videoBarStatus');
    $item['title'] = "Google Video";
    $item['url'] = "http://www.google.com";
    
    $items[] = $item;
    return $items; 
  }
}