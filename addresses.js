/**
 * $Id$
 * @author Cody Craven
 * @file addresses.js
 *
 * Rebuild province field with a select list of provinces for country selected
 * on load and on change.
 */
Drupal.behaviors.addresses = function(context) {
  // Bind country changes to reload the province field and
  // load province select element onLoad, do it once.
  // See http://drupal.org/node/817244
  $('.addresses-country-field:not(.addresses-processed)',context)
    .addClass('addresses-processed')
    .bind('change',function(){performProvinceAjax(this);})
    .change();

  // Make province select list call
  function performProvinceAjax(countryElement) {
    // Country field's related province element
    var provinceElement=$(countryElement).parent().siblings().children('.addresses-province-field');

    $.ajax({
      type:'GET',
      url:Drupal.settings.basePath,
      success:updateProvinceField,
      dataType:'json',
      data: {
        q:'addresses/province_ajax',
        country:$(countryElement).val(),
        field_id:provinceElement.attr('id'),
        field_name:provinceElement.attr('name'),
        passback:provinceElement.parent().attr('id'),
        province:provinceElement.val()
      }
    });
  }

  // Populate province field
  function updateProvinceField(data) {
    if(data.hide){
      $('#'+data.passback).hide();
    }else{
      $('#'+data.passback).show();
    }
    $('#'+data.passback).html(data.field);
  }
};
