<?php
/**
 * @file morelikethis_flickr.class.inc
 */
 
abstract class FlickrBase extends MoreLikeThisBase {

  protected function searchFlickr() {

    $flickr = flickrapi_phpFlickr();
    $tags = implode(", ", $this->terms);
    
    // http://www.flickr.com/services/api/flickr.photos.search.html
    
    $params = array( 
      'api_key' => variable_get('flickrapi_api_key', ''),
      'tags'=>$tags, 
      'per_page'=>variable_get('flickr_api_page_size', '10'), 
      'extras'=>'tags', 
      'safe_search'=>variable_get('flickr_api_page_safe_search', '1'), 
      'sort'=>'relevance', 
      'content_type'=> 1,
      'tag_mode' => variable_get('flickr_api_page_tag_mode', 'any')
    );

    $photos = $flickr->photos_search($params);
    $photos['search_tags'] = $tags;
    
    return $photos;
  }
  
  /**
   * Return the term with a higher relevance score
   */
  protected function term_more_relevant($term1, $term2 = NULL) {
	  if($term2 == NULL)
	    return $term1;
	
	  if ((float)$term1->relevance > (float)$term2->relevance ) {
	    return $term1;  
	  }
	  return $term2;
	}  
} 

class MoreLikeThisFlickr extends FlickrBase {
  
  public function isEnabled($type) {
    $key = drupal_strtolower($type);
    return variable_get("morelikethis_flickr_content_type_$key", FALSE);
}

  public function find($settings = array()) {
    $items = array();
    $thumbsize = variable_get('flickr_api_thumbnail_size', 's');
    $flickr_photos = $this->searchFlickr();
    
    if($flickr_photos['photo']) {
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
    }
	 
    $items['search_tags'] = $flickr_photos['search_tags'];
  	return $items;
  }
}