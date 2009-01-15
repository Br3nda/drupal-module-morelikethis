Drupal.behaviors.mlt_flickr_info = function(context){
  $('ul.mlt-flickr li').hover(
    function(){ $(this).children('.tags').show();},
    function(){ $(this).children('.tags').hide();}
   );
   $('#block-morelikethis-flickr h2').hover(
     function(){ $('#block-morelikethis-flickr .search-with').show();},
     function(){ $('#block-morelikethis-flickr .search-with').hide();}
   );
};
