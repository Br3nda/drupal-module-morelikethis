; $Id: README.txt,v 1.1.2.4 2009/01/23 16:44:29 febbraro Exp $

More Like This
--------------
More Like This provides a framework for providing related content. This data is provided as a block to be manipulated during theming.

Configuration
-------------
If you have the Calais module also installed (http://drupal.org/project/opencalais) you have the option of pre-filling your More Like This terms based on Calais Suggestions.  The field called "Global Term Relevancy Threshold for MLT" is used to limit which terms are applied based on the relevance score returned form Calais. The value is specified as a number that ranges from 0.0 to 1.0.  Specifying 0.0 will use all Calais Terms (there will be quite a few, many of which will be irrelevant). Specifying 1.0 will almost guarantee no significant terms.  We have found that a value around 0.55-0.7 works pretty well, but should be tested on your content first.

Theme
--------------
There are a few theming options for More Like This results.

theme_morelikethis_block($items)
This is the general theme function for the blocks. It takes a list of the More Like This classes (detailed
below in the node properties).  It iterates each item and calls the theme function for each individual item.

theme_morelikethis_item($item)
This formats an individual related item for display. It currently creates a link to the related node and the
link text is the node title with the relevance percentage. Example: Node Title (80%)

Current Providers
----------------
These modules can be found in the contrib/ directory.
 - Taxonomy
 - Flickr
 - Google Video
 - Yahoo! BOSS Web/News Search
 - Yahoo! BOSS Image Search


Future Providers
----------------
This initial release includes one type of search based on Taxonomy. Over the course of a few release we will 
develop a pluggable architecture for search providers to integrate other mechanisms for finding related content.

These might include:
 - Local Calais recommendataions
 - Internal Drupal content search
 - Apache Solr instances

 
Building a MoreLikeThis Plugin
------------------------------
If you look into the contrib directory, you will see other modules that provide
the MoreLikeThis (MLT) module with other types of related content.  It is here 
that you can integrate MLT with other services. 
 
For the most part, creating a MLT plugin is as easy as building any drupal 
module.  You will need at least three files,  a module, info, and class file.
 - module file: Implements MLT module hooks, admin settings, theming overrides.
 - info file: basic info file for a Drupal Module.  See drupal.org, 
   http://drupal.org/node/231036
 - class file: Extends the morelikethis base class and provides implementation 
   for the find() method.
 - * you can also use an install file if needed to setup requirements or 
     database changes needed for your module, but its not required.  
    
So where do you start?
 - Create a new directory under morelikethis/contrib named 
   morelikethis_newservice.
 - Next create placeholders for morelikethis_newservice.info file, 
   morelikethis_newservice.module file and morelikethis_newservice.class.inc 
   files.  You can also just unzip the morlikethis_newservice.zip for a basic 
   structure.
 - Now, we want to implement hook_morelikethis, so the MLT module will know 
   about our service.
 
 function morelikethis_newservice_morelikethis() {
   return array(
    'newservice' => array(
      '#title' => 'More Like This New Service',
      '#description' => 'Lookup related content using my New Service',
      '#class' => 'MoreLikeThisNewService',
      '#classfile' => 'morelikethis_newservice.class.inc',
      '#settings' => 'morelikethis_newservice_settings',
    ),
  );
}
  
The Module Settings
-------------------
 - With this done, the MLT module knows about our service (if enabled), and if
   you have the 'settings' function implemented in your module file, you 
   should see it as an option on the 'admin/settings/morelikethis' page after 
   clearing the site cache. (devel/cache/clear).
 - If you look on the block listing page, (admin/build/block/list), You will 
   see a new block. This is where the items from your service will be presented.

Implement find() and isEnabled().
 - isEnabled has to be implemented correctly for the service to run.  Return a 
   simple boolean based off of the admin settings best for your service.
 - Open up the morelikethis_<yourservice>.class.inc file and create the find 
   method.  Use the NewService example as a basic guide or any of the other 
   contrib modules for more in depth examples.  At a minimum, the find() method
   needs to return an array of objects or arrays with 'title' and 'url' 
   properties.  It can also have more properties specified by the specific 
   implementation.

Output Theming      
 - Theming is simple enough, just make sure you use the naming convention set
   forth by the framework.  
   The convention is:
      theme_morelikethis_<MORE-LIKE-THIS-SERVICE-NAME>_item 
      and
      theme_morelikethis_<MORE-LIKE-THIS-SERVICE-NAME>_block
 - You can see where this happens in the _morelikethis_build_node_properties(), 
   theme_morelikethis_block() and _mlt_block_view() functions of the 
   morelikethis.module.  
 - Once the $items variable contains data, the theming of the block and items
   are pretty straight forward.
 
Troubleshooting
---------------
 - Make sure you have hook_theme implemented for your module.
 - clear cache with devel module
 - check your isEnabled method to make sure it's return what you expect.
 - Be sure you are trying to theme the same type of item.  Find can return an 
   array of objects or arrays.  Make sure your item theme is using whatever 
   your find() method returns.
 - During development of your service, when saving the block admin page, you 
   might receive an Access Denied error.  None of your changes will be saved.  
   I'm not sure the exact cause of this, but clearing the cache and making 
   sure all the theming functions can be found usually helps with this.