// $Id: morelikethis.js,v 1.1 2008/10/03 16:36:58 febbraro Exp $

/**
 * Add the UI functionality for the term selction.
 */
Drupal.behaviors.moreLikeThis = function(context) {
	var list = $('#edit-morelikethis-taxonomy-terms', context);
	list.click(function() {
		var terms = $('#edit-morelikethis-terms');

		termVal = jQuery.trim(terms.val());
		if(termVal.length > 0) {
			termVal += ',';
		}
		
		// Wrap in quotes if term has a comma in it
		keyword = $(this).val();
		if(keyword.indexOf(',') != -1) {
	    keyword = '"' + keyword + '"'
		}
		
		terms.val(termVal + keyword);
	});
};

