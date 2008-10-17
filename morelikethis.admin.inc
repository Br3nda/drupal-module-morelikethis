<?php
/*
  Copyright (C) 2008 by Phase2 Technology.
  Author(s): Frank Febbraro

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License.
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY. See the LICENSE.txt file for more details.

  $Id: morelikethis.admin.inc,v 1.1.2.1 2008/10/17 21:42:37 febbraro Exp $
 */
/**
 * @file morelikethis.admin.inc
 */

/**
 * Settings for More Like This functionality.
 */
function morelikethis_settings() {
  $services = _morelikethis_providers();

  drupal_set_title('More Like This Configuration Settings');
  
  $items = array();
  foreach ($services as $key=> $service) {
    $items[] = l($service['title'], "admin/settings/morelikethis/$key");
  }

  return theme('item_list', $items);
}
