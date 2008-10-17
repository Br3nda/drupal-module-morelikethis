<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.class.inc,v 1.1.2.1 2008/10/17 21:42:37 febbraro Exp $
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
   *
   */
  public function setNode($node);

  /**
   *
   */
  public function addTerm($term);

  /**
   *
   */
  public function find();
}

abstract class MoreLikeThisBase implements MoreLikeThis  {
  
  public $node;
  public $terms;
  
  function __construct($node = NULL, $terms = array()) {
    $this->node = $node;
    $this->terms = $terms;
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
