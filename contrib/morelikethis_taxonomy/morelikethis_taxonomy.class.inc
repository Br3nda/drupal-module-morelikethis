<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis_taxonomy.class.inc,v 1.1.2.3 2009/01/07 21:09:33 emackn Exp $
*/
/**
 * @file morelikethis_taxonomy.class.inc
 */

/**
 * More Like This service provider for Taxonomy term matching.
 */
class MoreLikeThisTaxonomy extends MoreLikeThisBase {
  
  public function isEnabled($type) {
    $key = drupal_strtolower($type);
    return variable_get("morelikethis_taxonomy_enabled_{$key}", FALSE);
  }
  
  public function find($settings = array()) {
    
    $term_count = count($this->terms);
    if($term_count == 0)
      return FALSE;

    $key = drupal_strtolower($this->node->type);
    $types = variable_get("morelikethis_taxonomy_target_types_{$key}", FALSE);
    if(empty($types))
      return FALSE;

    $types = array_keys($types);
    $count = variable_get("morelikethis_taxonomy_count_{$key}", NULL);
    $count = empty($count) ? 10 : intval($count);
    $threshold = floatval(variable_get("morelikethis_taxonomy_threshold_{$key}", 0));

    $sql = "SELECT n.nid, n.type, n.title, count(*) as hits, count(*)/$term_count as relevance";
    $sql .= " FROM {node} n";
    $sql .= " JOIN {term_node} tn ON n.nid = tn.nid";
    $sql .= " JOIN {term_data} td ON tn.tid = td.tid";
    $sql .= " WHERE n.nid <> %d";
    $sql .= " AND n.type IN (" . db_placeholders($types, 'varchar') . ")";
    $sql .= " AND td.name IN (" . db_placeholders($this->terms, 'varchar') . ")";
    $sql .= " AND n.status = 1";
    $sql .= " GROUP BY n.nid";
    $sql .= " HAVING relevance >= %f";
    $sql .= " ORDER BY hits DESC, n.nid DESC";
    $args = array_merge(array($this->node->nid), $types, $this->terms, array($threshold));

    $result = db_query_range($sql, $args, 0, $count);

    $likeness = array();
    while($likenode = db_fetch_object($result)) {
      $likenode->id = $likenode->nid;
      $likenode->url = "node/$likenode->nid";
      $likenode->mlt_type = 'taxonomy';
      $likeness[] = $likenode;
    }
		
    return $likeness;
  }  
}

