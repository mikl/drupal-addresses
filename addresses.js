/**
 * $Id$
 * @author Cody Craven
 * @file addresses.js
 *
 * Rebuild province field with a select list of provinces for country selected
 * on load and on change.
 */
Drupal.behaviors.addresses = function(context) {
  // Load province select element onLoad
  performProvinceAjax($('.addresses-country-field'));

  // Bind country changes to reload the province field
  $('.addresses-country-field').bind('change', function() {
    performProvinceAjax(this);
  });

  // Make province select list call
  function performProvinceAjax(countryElement) {
    // Country field's related province element
    var provinceElement = $(countryElement).parent().siblings().children('.addresses-province-field');

    $.ajax({
      type: 'GET',
      url: Drupal.settings.basePath + 'addresses/province_ajax',
      success: updateProvinceField,
      dataType: 'json',
      data: {
        country:$(countryElement).val(),
        field_id:provinceElement.attr('id'),
        field_name:provinceElement.attr('name'),
        passback:provinceElement.parent().attr('id'),
        province:provinceElement.val(),
      },
    });
  }

  // Populate province field
  function updateProvinceField(data) {
    if (data.hide) {
      $('#' + data.passback).hide();
    } else {
      $('#' + data.passback).show();
    }
    $('#' + data.passback).html(data.field);
  }
};
