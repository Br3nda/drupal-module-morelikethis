; $Id: README.txt,v 1.1.2.1 2009/01/23 16:44:49 febbraro Exp $

More Like This Taxonomy
------------------------
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
   
   * Enabled      - Is More Like This functionality provided for this specific Content Type
   * Target Types - Which other site Content Type will be searched as related content
   * Count        - The maximum number of entries to return in the More Like This query/listing
   * Threshold    - This is a filter on More Like This results based on a percentage of matching Terms
   
To sum up the configuration, if enabled, More Like This for a specfic content type will search for existing 
content of the specified target types ordered by relevance that meet a certain threshold of matched terms and
will return no more than the specified count. Sounds easy right? :)
