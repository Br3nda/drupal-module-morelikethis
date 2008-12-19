// $Id: morelikethis.js,v 1.1.2.1 2008/12/19 22:15:17 febbraro Exp $

/**
 * Add the UI functionality for the term selction.
 */
Drupal.behaviors.moreLikeThis = function(context) {
	// Bind to the Taxonomy Term list
	$('#edit-morelikethis-taxonomy-terms', context).click(function() {
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
	
	// Setup the Calais checkbox
	if ($("#edit-morelikethis-use-calais-defaults").size() && $("#edit-morelikethis-use-calais-defaults").attr("checked")) {
    // Hide its description and the taxonomy selector
    $("#edit-morelikethis-terms").attr("disabled","disabled");
    $("#edit-morelikethis-terms-wrapper > div.description").hide(0);
    $("#edit-morelikethis-taxonomy-terms-wrapper").hide(0);
  }
  $("#edit-morelikethis-use-calais-defaults").click(function() {
    if ($("#edit-morelikethis-use-calais-defaults").attr("checked")) {
			// Use Calais is clicked. Disable/hide fields
      $("#edit-morelikethis-terms").attr("disabled","disabled");
      $("#edit-morelikethis-terms-wrapper > div.description").slideUp('fast');
	    $("#edit-morelikethis-taxonomy-terms-wrapper").slideUp('fast');
    }
    else { // Unchecked show it all
      $("#edit-morelikethis-terms").removeAttr("disabled");
      $("#edit-morelikethis-terms-wrapper > div.description").slideDown('fast');
	    $("#edit-morelikethis-taxonomy-terms-wrapper").slideDown('fast');
    }
  });
  
};

