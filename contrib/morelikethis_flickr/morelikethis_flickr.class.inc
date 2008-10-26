<?php
/**
 * @file morelikethis_flickr.class.inc
 */
 
abstract class FlickrBase extends MoreLikeThisBase {

  protected function searchFlickr() {

    $flickr = flickrapi_phpFlickr();
    $tags = $this->get_calais_terms();

    // http://www.flickr.com/services/api/flickr.photos.search.html
    $params = array( 'tags'=>$tags, 'per_page'=>10, 'extras'=>'tags', 
      'safe_search'=>1, 'sort'=>'relevance', 'content_type'=> 1);

    $photos = $flickr->photos_search($params);
    $photos['search_tags'] = $tags;
    
    return $photos;
  }
  
  
  protected function get_calais_terms($threshold = 0.25, $delimeter = ", ") {
    $n = $this->node;
  	
    $calais_suggestions = calais_get_keywords($n->nid, $n->type);
    
    foreach($calais_suggestions as $vocab) {
      if(empty($vocab))
        continue;
    
	    foreach($vocab as $term) {
	      $c_term = calais_get_node_term($n->nid, $term);
	      
	      $most_relevant = term_more_relevant($c_term, $most_relevant);
	      
	      if((float)$c_term->relevance >= (float)$threshold) {
	        $tags[$c_term->relevance*1000] = $term;
	      }
	    }
    }
    if(empty($tags)){
      $tags[] = $most_relevant->value;
    }

    return implode($delimeter, $tags);
    
  }

} 

class MoreLikeThisFlickr extends FlickrBase {
  
  public function isEnabled($type) {
    return TRUE;
  }

  public function find($settings = array()) {
    $items = array();
    
    $thumbsize = variable_get('flickr_api_thumbnail_size', 's');
    $flickr_photos = $this->searchFlickr();
    
    foreach ($flickr_photos['photo'] as $photo) {
	    $items[] = array(
	      'url' => "http://farm". $photo['farm'] .".static.flickr.com/". $photo['server'] ."/". 
	         $photo['id'] ."_". $photo['secret'] ."_". $thumbsize .".jpg", 
	      'title' => $photo['title'],
	      'id' => $photo['id'],
	      'tags' => $photo['tags'],
	      'owner' => $photo['owner'],
	      'secret' => $photo['secret'],
	      'server' => $photo['secret'],
	      'farm' => $photo['farm'],
	    );
    }
	 
    $items['search_tags'] = $flickr_photos['search_tags'];
  	return $items;
  }
}