/**
 * $Id$
 * @author Bruno Massa
 * @file addresses.js
 * Autocompletion for Province field.
 * This jQuery function will force the Province field
 * to autcomplete the pronvice for a given country.
 */

Drupal.behaviors.addresses = function(context) {
  // Use this ID to 'simplify' the callings
  var id = '#edit-addresses-';

  // Record the original URL
  var url = Drupal.settings.absPath + '/admin/settings/addresses/autocomplete/';

  // Get all address
  for (var n = 0; true; n++) {
    // Check if this Field exists.
    // If not, stop the script
    if (!$(id + n +'-country').length) {
      break;
    }

    // Set the country code at the beginning
    if ($(id + n +'-country').val()) {
      $(id + n +'-province-autocomplete').val(url + $(id + n +'-country').val());
    }

    // Change the country code everytime the country field changes
    $(id + n +'-country').change(function() {
      $(id + n +'-province-autocomplete').val(url + $(this).val());
//       Drupal.behaviors.autocomplete();
    })
  }
};
