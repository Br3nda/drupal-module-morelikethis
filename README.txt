; $Id: README.txt,v 1.1.2.1 2008/10/17 21:42:37 febbraro Exp $

More Like This
--------------
More Like This provides a mechanism (and soon a framework) for providing related content. It currently only 
supports and internal taxonomy search, but the plan is to open it up with a framework for
plugging in morelikethis providers.  This data is provided either as a block or as node
properties to be manipulated during theming.

Taxonomy Lookup
---------------
This initial release includes a taxonomy based lookup mechanism for More Like This content. It works by first
specifying your "Thumbprint" for a particular node on the node edit form. By thumbprint we mean you can specify
the terms/words that you, as an editor, feel uniquely identifies this content item.  You can either select existing
taxonomy terms associated with this specific node, or enter free hand terms.  When performing the lookup we will 
determine what other nodes in the site match the provided More Like This terms and those with the highest 
relevance/hit count will appear first in the list.

Configuration
--------------
From Site Configuration -> More Like This settings you can configure the various settings that control
the functionality.  More Like This is configured on a per Content Type basis and allows you to configure 
the following features:
   
   * Enabled - Is More Like This functionality provided for this specific Content Type
   * Target Types - Which other site Content Type will be searched as related content
   * Count - The maximum number of entries to return in the More Like This query/listing
   * Threshold - This is a filter on More Like This results based on a percentage of matching Terms
   
To sum up the configuration, if enabled, More Like This for a specfic content type will search for existing 
content of the specified target types ordered by relevance that meet a certain threshold of matched terms and
will return no more than the specified count. Sounds easy right? :)

Theme
--------------
There are a few theming options for More Like This results.

theme_morelikethis_block($items)
This is the general theme function for the blocks. It takes a list of the More Like This classes (detailed
below in the node properties).  It iterates each item and calls the theme function for each individual item.

theme_morelikethis_item($item)
This formats an individual related item for display. It currently creates a link to the related node and the
link text is the node title with the relevance percentage. Example: Node Title (80%)


Node Properties
---------------
The node properties are specified as such:

$node->morelikethis = array(
  [0] => array(
    ['#view'] => '<a href="some/node/path">Node Title (80%)</a>',
    ['#item'] => object(stdClass)#18 (4) {
      ["id"]=> "183"
      ["title"]=> "Node Title"
      ["url"]=> "node/183"
      ["mlt_type"]=> "taxonomy"
      
      // Optional properties provided by the modules may be...
      ["nid"]=> "183"
      ["type"]=> "story"
      ["hits"]=> "4"
      ["relevance"]=> "0.8"
    }
  )
)

You can theme them within an existing node.tpl.php with:

<?php if ($node->morelikethis): ?>
  <div class="morelikethis">
    <h3>More Like This</h3>
    <?php
      $items = array();
      foreach ($node->morelikethis as $item) {
        $items[] = $item['#view'];          
      }
      print theme('item_list', $items);
    ?>
  </div>
<?php endif;?>

Future Providers
----------------
This initial release includes one type of search based on Taxonomy. Over the course of a few release we will 
develop a pluggable architecture for search providers to integrate other mechanisms for finding related content.

These might include:
 - Local Calais recommendataions
 - Apache Solr instances
 - Internal Drupal content search
 - Yahoo BOSS Service
 - Google
