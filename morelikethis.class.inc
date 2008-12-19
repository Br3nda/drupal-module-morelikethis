<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.class.inc,v 1.1.2.3 2008/12/19 22:22:36 febbraro Exp $
*/
/**
 * @file morelikethis.class.inc
 */

/**
 * Interface defining the operations required for all MoreLikeThis Service Providers.
 */
interface MoreLikeThis {

  /**
   * Is this MoreLikeThis provider enabled for the provided node type.
   *
   * @param $type
   *    Content Type 
   * @return
   *    True if the service provider is enabled for the provided content type.
   */
  public function isEnabled($type);
  
  /**
   * Initialize the context of a MoreLikeThis Search.
   *
   * @param $term
   *    A term or an array of terms to specify on the search.
   * @param $node
   *    The node to find content about.
   */
  public function init($term, $node);

  /**
   * Find related content.
   *
   * @param $settings
   *    Override settings on the class with this array.
   * @return
   *    An array of related content objects (or arrays).
   *    Return fields should have at a minimum the following properties:
   *     - url   : The URL to the content
   *     - title : The title of the content
   */
  public function find($settings = array());
}

/**
 * Base class implementation of the MoreLikeThis interface.
 */
abstract class MoreLikeThisBase implements MoreLikeThis  {
  
  public $node = NULL;
  public $terms = array();
  
  public function init($term, $node) {
    $this->addTerm($term);
    $this->setNode($node);
  }
  
  public function setNode($node) {
    $this->node = $node;
  }
  
  public function addTerm($term) {
    if(is_array($term)) {
      $this->terms = array_merge($this->terms, $term);
    }
    else {
      $this->terms[] = $term;
    }
  }
  
} 
