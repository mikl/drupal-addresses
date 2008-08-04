<?php
// $Id$
/**
 * @author Bruno Massa
 * @file addresses.inc
 * An implementation of a universal API for address manipulation.
 */

/**
 * List all countries on Planet! :)
 *
 * It uses the ISO notation.
 * See http://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
 * or http://www.iso.org/iso/country_codes/iso_3166_code_lists/english_country_names_and_code_elements.htm
 * for further info.
 *
 * @param $available
 *   String (optional). A list of countries that are allowed.
 * @param $upper
 *   Boolean (optional). When TRUE, the country codes will
 *   be totally in Upper Case. Its the default ISO code,
 *   but the files and function are all named with lower
 *   case, so its better to return lower case by default
 * @return
 *   Array. 'COUNTRY CODE' => 'COUNTRY CODE' pairs as layed out in
 *   ISO 3166-1 alpha-2
 */
function _addresses_country_get($available = array(), $upper = FALSE) {
  $countries = array(
    'ad' => t('Andorra'),
    'ae' => t('United Arab Emirates'),
    'af' => t('Afghanistan'),
    'ag' => t('Antigua and Barbuda'),
    'ai' => t('Anguilla'),
    'al' => t('Albania'),
    'am' => t('Armenia'),
    'an' => t('Netherlands Antilles'),
    'ao' => t('Angola'),
    'aq' => t('Antarctica'),
    'ar' => t('Argentina'),
    'as' => t('American Samoa'),
    'at' => t('Austria'),
    'au' => t('Australia'),
    'aw' => t('Aruba'),
    'ax' => t('Aland Islands'),
    'az' => t('Azerbaijan'),
    'ba' => t('Bosnia and Herzegovina'),
    'bb' => t('Barbados'),
    'bd' => t('Bangladesh'),
    'be' => t('Belgium'),
    'bf' => t('Burkina Faso'),
    'bg' => t('Bulgaria'),
    'bh' => t('Bahrain'),
    'bi' => t('Burundi'),
    'bj' => t('Benin'),
    'bm' => t('Bermuda'),
    'bn' => t('Brunei'),
    'bo' => t('Bolivia'),
    'br' => t('Brazil'),
    'bs' => t('Bahamas'),
    'bt' => t('Bhutan'),
    'bv' => t('Bouvet Island'),
    'bw' => t('Botswana'),
    'by' => t('Belarus'),
    'bz' => t('Belize'),
    'ca' => t('Canada'),
    'cc' => t('Cocos (Keeling) Islands'),
    'cd' => t('Congo (Kinshasa)'),
    'cf' => t('Central African Republic'),
    'cg' => t('Congo (Brazzaville)'),
    'ch' => t('Switzerland'),
    'ci' => t('Ivory Coast'),
    'ck' => t('Cook Islands'),
    'cl' => t('Chile'),
    'cm' => t('Cameroon'),
    'cn' => t('China'),
    'co' => t('Colombia'),
    'cr' => t('Costa Rica'),
    'cs' => t('Serbia And Montenegro'),
    'cu' => t('Cuba'),
    'cv' => t('Cape Verde'),
    'cx' => t('Christmas Island'),
    'cy' => t('Cyprus'),
    'cz' => t('Czech Republic'),
    'de' => t('Germany'),
    'dj' => t('Djibouti'),
    'dk' => t('Denmark'),
    'dm' => t('Dominica'),
    'do' => t('Dominican Republic'),
    'dz' => t('Algeria'),
    'ec' => t('Ecuador'),
    'ee' => t('Estonia'),
    'eg' => t('Egypt'),
    'eh' => t('Western Sahara'),
    'er' => t('Eritrea'),
    'es' => t('Spain'),
    'et' => t('Ethiopia'),
    'fi' => t('Finland'),
    'fj' => t('Fiji'),
    'fk' => t('Falkland Islands'),
    'fm' => t('Micronesia'),
    'fo' => t('Faroe Islands'),
    'fr' => t('France'),
    'ga' => t('Gabon'),
    'gd' => t('Grenada'),
    'ge' => t('Georgia'),
    'gf' => t('French Guiana'),
    'gg' => t('Guernsey'),
    'gh' => t('Ghana'),
    'gi' => t('Gibraltar'),
    'gl' => t('Greenland'),
    'gm' => t('Gambia'),
    'gn' => t('Guinea'),
    'gp' => t('Guadeloupe'),
    'gq' => t('Equatorial Guinea'),
    'gr' => t('Greece'),
    'gs' => t('South Georgia and the South Sandwich Islands'),
    'gt' => t('Guatemala'),
    'gu' => t('Guam'),
    'gw' => t('Guinea-Bissau'),
    'gy' => t('Guyana'),
    'hk' => t('Hong Kong S.A.R., China'),
    'hm' => t('Heard Island and McDonald Islands'),
    'hn' => t('Honduras'),
    'hr' => t('Croatia'),
    'ht' => t('Haiti'),
    'hu' => t('Hungary'),
    'id' => t('Indonesia'),
    'ie' => t('Ireland'),
    'il' => t('Israel'),
    'im' => t('Isle of Man'),
    'in' => t('India'),
    'io' => t('British Indian Ocean Territory'),
    'iq' => t('Iraq'),
    'ir' => t('Iran'),
    'is' => t('Iceland'),
    'it' => t('Italy'),
    'je' => t('Jersey'),
    'jm' => t('Jamaica'),
    'jo' => t('Jordan'),
    'jp' => t('Japan'),
    'ke' => t('Kenya'),
    'kg' => t('Kyrgyzstan'),
    'kh' => t('Cambodia'),
    'ki' => t('Kiribati'),
    'km' => t('Comoros'),
    'kn' => t('Saint Kitts and Nevis'),
    'kp' => t('North Korea'),
    'kr' => t('South Korea'),
    'kw' => t('Kuwait'),
    'ky' => t('Cayman Islands'),
    'kz' => t('Kazakhstan'),
    'la' => t('Laos'),
    'lb' => t('Lebanon'),
    'lc' => t('Saint Lucia'),
    'li' => t('Liechtenstein'),
    'lk' => t('Sri Lanka'),
    'lr' => t('Liberia'),
    'ls' => t('Lesotho'),
    'lt' => t('Lithuania'),
    'lu' => t('Luxembourg'),
    'lv' => t('Latvia'),
    'ly' => t('Libya'),
    'ma' => t('Morocco'),
    'mc' => t('Monaco'),
    'md' => t('Moldova'),
    'me' => t('Montenegro'),
    'mg' => t('Madagascar'),
    'mh' => t('Marshall Islands'),
    'mk' => t('Macedonia'),
    'ml' => t('Mali'),
    'mm' => t('Myanmar'),
    'mn' => t('Mongolia'),
    'mo' => t('Macao S.A.R., China'),
    'mp' => t('Northern Mariana Islands'),
    'mq' => t('Martinique'),
    'mr' => t('Mauritania'),
    'ms' => t('Montserrat'),
    'mt' => t('Malta'),
    'mu' => t('Mauritius'),
    'mv' => t('Maldives'),
    'mw' => t('Malawi'),
    'mx' => t('Mexico'),
    'my' => t('Malaysia'),
    'mz' => t('Mozambique'),
    'na' => t('Namibia'),
    'nc' => t('New Caledonia'),
    'ne' => t('Niger'),
    'nf' => t('Norfolk Island'),
    'ng' => t('Nigeria'),
    'ni' => t('Nicaragua'),
    'nl' => t('Netherlands'),
    'no' => t('Norway'),
    'np' => t('Nepal'),
    'nr' => t('Nauru'),
    'nu' => t('Niue'),
    'nz' => t('New Zealand'),
    'om' => t('Oman'),
    'pa' => t('Panama'),
    'pe' => t('Peru'),
    'pf' => t('French Polynesia'),
    'pg' => t('Papua New Guinea'),
    'ph' => t('Philippines'),
    'pk' => t('Pakistan'),
    'pl' => t('Poland'),
    'pm' => t('Saint Pierre and Miquelon'),
    'pn' => t('Pitcairn'),
    'pr' => t('Puerto Rico'),
    'ps' => t('Palestinian Territory'),
    'pt' => t('Portugal'),
    'pw' => t('Palau'),
    'py' => t('Paraguay'),
    'qa' => t('Qatar'),
    're' => t('Reunion'),
    'ro' => t('Romania'),
    'rs' => t('Serbia'),
    'ru' => t('Russia'),
    'rw' => t('Rwanda'),
    'sa' => t('Saudi Arabia'),
    'sb' => t('Solomon Islands'),
    'sc' => t('Seychelles'),
    'sd' => t('Sudan'),
    'se' => t('Sweden'),
    'sg' => t('Singapore'),
    'sh' => t('Saint Helena'),
    'si' => t('Slovenia'),
    'sj' => t('Svalbard and Jan Mayen'),
    'sk' => t('Slovakia'),
    'sl' => t('Sierra Leone'),
    'sm' => t('San Marino'),
    'sn' => t('Senegal'),
    'so' => t('Somalia'),
    'sr' => t('Suriname'),
    'st' => t('Sao Tome and Principe'),
    'sv' => t('El Salvador'),
    'sy' => t('Syria'),
    'sz' => t('Swaziland'),
    'tc' => t('Turks and Caicos Islands'),
    'td' => t('Chad'),
    'tf' => t('French Southern Territories'),
    'tg' => t('Togo'),
    'th' => t('Thailand'),
    'tj' => t('Tajikistan'),
    'tk' => t('Tokelau'),
    'tl' => t('East Timor'),
    'tm' => t('Turkmenistan'),
    'tn' => t('Tunisia'),
    'to' => t('Tonga'),
    'tr' => t('Turkey'),
    'tt' => t('Trinidad and Tobago'),
    'tv' => t('Tuvalu'),
    'tw' => t('Taiwan'),
    'tz' => t('Tanzania'),
    'ua' => t('Ukraine'),
    'ug' => t('Uganda'),
    'uk' => t('United Kingdom'),
    'um' => t('United States Minor Outlying Islands'),
    'us' => t('United States'),
    'uy' => t('Uruguay'),
    'uz' => t('Uzbekistan'),
    'va' => t('Vatican'),
    'vc' => t('Saint Vincent and the Grenadines'),
    've' => t('Venezuela'),
    'vg' => t('British Virgin Islands'),
    'vi' => t('U.S. Virgin Islands'),
    'vn' => t('Vietnam'),
    'vu' => t('Vanuatu'),
    'wf' => t('Wallis and Futuna'),
    'ws' => t('Samoa'),
    'ye' => t('Yemen'),
    'yt' => t('Mayotte'),
    'za' => t('South Africa'),
    'zm' => t('Zambia'),
    'zw' => t('Zimbabwe'),
  );

  if (!empty($available)) {
    foreach ($countries as $ccode => $country) {
      if (empty($available[$ccode])) {
        unset($countries[$ccode]);
      }
    }
  }

  // In fact, the ISO codes for countries are all Upper Case.
  // So, if someone needs the list as the official records,
  // it will convert.
  if (!empty($upper)) {
    $countries = array_change_key_case($countries, CASE_UPPER);
  }

  // Sort the list and return
  natcasesort($countries);

  return $countries;
}

/**
 * 3-diget code of all countries on Planet! :)
 *
 * It uses the ISO notation.
 * See http://en.wikipedia.org/wiki/ISO_3166-1_alpha-3
 * for further info.
 *
 * @return
 *   Array. 'COUNTRY 2-DIGIT CODE' => 'COUNTRY 3-DIGIT CODE' pairs
 */
function _addresses_country_get_code3() {
  $countries = array(
    'af' => 'afg',
    'ax' => 'ala',
    'al' => 'alb',
    'dz' => 'dza',
    'as' => 'asm',
    'ad' => 'and',
    'ao' => 'ago',
    'ai' => 'aia',
    'aq' => 'ata',
    'ag' => 'atg',
    'ar' => 'arg',
    'am' => 'arm',
    'aw' => 'abw',
    'au' => 'aus',
    'at' => 'aut',
    'az' => 'aze',
    'bs' => 'bhs',
    'bh' => 'bhr',
    'bd' => 'bgd',
    'bb' => 'brb',
    'by' => 'blr',
    'be' => 'bel',
    'bz' => 'blz',
    'bj' => 'ben',
    'bm' => 'bmu',
    'bt' => 'btn',
    'bo' => 'bol',
    'ba' => 'bih',
    'bw' => 'bwa',
    'bv' => 'bvt',
    'br' => 'bra',
    'io' => 'iot',
    'bn' => 'brn',
    'bg' => 'bgr',
    'bf' => 'bfa',
    'bi' => 'bdi',
    'kh' => 'khm',
    'cm' => 'cmr',
    'ca' => 'can',
    'cv' => 'cpv',
    'ky' => 'cym',
    'cf' => 'caf',
    'td' => 'tcd',
    'cl' => 'chl',
    'cn' => 'chn',
    'cx' => 'cxr',
    'cc' => 'cck',
    'co' => 'col',
    'km' => 'com',
    'cg' => 'cog',
    'cd' => 'zar',
    'ck' => 'cok',
    'cr' => 'cri',
    'ci' => 'civ',
    'hr' => 'hrv',
    'cu' => 'cub',
    'cy' => 'cyp',
    'cz' => 'cze',
    'dk' => 'dnk',
    'dj' => 'dji',
    'dm' => 'dma',
    'do' => 'dom',
    'ec' => 'ecu',
    'eg' => 'egy',
    'sv' => 'slv',
    'gq' => 'gnq',
    'er' => 'eri',
    'ee' => 'est',
    'et' => 'eth',
    'fk' => 'flk',
    'fo' => 'fro',
    'fj' => 'fji',
    'fi' => 'fin',
    'fr' => 'fra',
    'gf' => 'guf',
    'pf' => 'pyf',
    'tf' => 'atf',
    'ga' => 'gab',
    'gm' => 'gmb',
    'ge' => 'geo',
    'de' => 'deu',
    'gh' => 'gha',
    'gi' => 'gib',
    'gr' => 'grc',
    'gl' => 'grl',
    'gd' => 'grd',
    'gp' => 'glp',
    'gu' => 'gum',
    'gt' => 'gtm',
    'gg' => 'ggy',
    'gn' => 'gin',
    'gw' => 'gnb',
    'gy' => 'guy',
    'ht' => 'hti',
    'hm' => 'hmd',
    'va' => 'vat',
    'hn' => 'hnd',
    'hk' => 'hkg',
    'hu' => 'hun',
    'is' => 'isl',
    'in' => 'ind',
    'id' => 'idn',
    'ir' => 'irn',
    'iq' => 'irq',
    'ie' => 'irl',
    'im' => 'imn',
    'il' => 'isr',
    'it' => 'ita',
    'jm' => 'jam',
    'jp' => 'jpn',
    'je' => 'jey',
    'jo' => 'jor',
    'kz' => 'kaz',
    'ke' => 'ken',
    'ki' => 'kir',
    'kp' => 'prk',
    'kr' => 'kor',
    'kw' => 'kwt',
    'kg' => 'kgz',
    'la' => 'lao',
    'lv' => 'lva',
    'lb' => 'lbn',
    'ls' => 'lso',
    'lr' => 'lbr',
    'ly' => 'lby',
    'li' => 'lie',
    'lt' => 'ltu',
    'lu' => 'lux',
    'mo' => 'mac',
    'mk' => 'mkd',
    'mg' => 'mdg',
    'mw' => 'mwi',
    'my' => 'mys',
    'mv' => 'mdv',
    'ml' => 'mli',
    'mt' => 'mlt',
    'mh' => 'mhl',
    'mq' => 'mtq',
    'mr' => 'mrt',
    'mu' => 'mus',
    'yt' => 'myt',
    'mx' => 'mex',
    'fm' => 'fsm',
    'md' => 'mda',
    'mc' => 'mco',
    'mn' => 'mng',
    'me' => 'mne',
    'ms' => 'msr',
    'ma' => 'mar',
    'mz' => 'moz',
    'mm' => 'mmr',
    'na' => 'nam',
    'nr' => 'nru',
    'np' => 'npl',
    'nl' => 'nld',
    'an' => 'ant',
    'nc' => 'ncl',
    'nz' => 'nzl',
    'ni' => 'nic',
    'ne' => 'ner',
    'ng' => 'nga',
    'nu' => 'niu',
    'nf' => 'nfk',
    'mp' => 'mnp',
    'no' => 'nor',
    'om' => 'omn',
    'pk' => 'pak',
    'pw' => 'plw',
    'ps' => 'pse',
    'pa' => 'pan',
    'pg' => 'png',
    'py' => 'pry',
    'pe' => 'per',
    'ph' => 'phl',
    'pn' => 'pcn',
    'pl' => 'pol',
    'pt' => 'prt',
    'pr' => 'pri',
    'qa' => 'qat',
    're' => 'reu',
    'ro' => 'rou',
    'ru' => 'rus',
    'rw' => 'rwa',
    'bl' => 'blm',
    'sh' => 'shn',
    'kn' => 'kna',
    'lc' => 'lca',
    'mf' => 'maf',
    'pm' => 'spm',
    'vc' => 'vct',
    'ws' => 'wsm',
    'sm' => 'smr',
    'st' => 'stp',
    'sa' => 'sau',
    'sn' => 'sen',
    'rs' => 'srb',
    'sc' => 'syc',
    'sl' => 'sle',
    'sg' => 'sgp',
    'sk' => 'svk',
    'si' => 'svn',
    'sb' => 'slb',
    'so' => 'som',
    'za' => 'zaf',
    'gs' => 'sgs',
    'es' => 'esp',
    'lk' => 'lka',
    'sd' => 'sdn',
    'sr' => 'sur',
    'sj' => 'sjm',
    'sz' => 'swz',
    'se' => 'swe',
    'ch' => 'che',
    'sy' => 'syr',
    'tw' => 'twn',
    'tj' => 'tjk',
    'tz' => 'tza',
    'th' => 'tha',
    'tl' => 'tls',
    'tg' => 'tgo',
    'tk' => 'tkl',
    'to' => 'ton',
    'tt' => 'tto',
    'tn' => 'tun',
    'tr' => 'tur',
    'tm' => 'tkm',
    'tc' => 'tca',
    'tv' => 'tuv',
    'ug' => 'uga',
    'ua' => 'ukr',
    'ae' => 'are',
    'gb' => 'gbr',
    'us' => 'usa',
    'um' => 'umi',
    'uy' => 'ury',
    'uz' => 'uzb',
    'vu' => 'vut',
    've' => 'ven',
    'vn' => 'vnm',
    'vg' => 'vgb',
    'vi' => 'vir',
    'wf' => 'wlf',
    'eh' => 'esh',
    'ye' => 'yem',
    'zm' => 'zmb',
    'zw' => 'zwe'
  );

  return $countries;
}

/**
 * Get available states.
 *
 * @param $country
 *   String (optional). The 2-digit country code
 * @return
 *   Array. If $country is passed, then return an array
 *   of states for that country. If nothing is passed then return
 *   an array of countrys who have states, where each country contains
 *   an array of states.
 */
function _addresses_province_get($country = NULL) {
  static $provinces;

  // Get a list of countries
  $countries_all = _addresses_country_get();

  // Test if its needed to update the province list
  if (empty($country) and empty($provinces)) {
    // Get the countries list
    $countries = array_keys($countries_all);
    $update = TRUE;
  }
  elseif (!empty($country) and $countries_all[$country] and empty($provinces[$country])) {
    $countries[] = $country;
    $update = TRUE;
  }

  if (!empty($update)) {
    foreach ($countries as $country_code) {
      // Load country specifice code .inc file if it exists.
      // For example, if country_code for U.S. == 'us', load 'addresses.us.inc'
      include_once drupal_get_path('module', 'addresses') .'/countries/'. $country_code .'.inc';

      // If the country have a province list, load it
      $function = 'addresses_province_list_'. $country_code;
      if (function_exists($function)) {
        $provinces[$country_code] = $function();
      }
    }
  }

  // Return the states of a single country, if any
  if (!empty($country)) {
    if (isset($provinces[$country])) {
      return $provinces[$country];
    }
    else {
      return array();
    }
  }
  else {
    return $provinces;
  }
}

/**
 * Generates HTML for the passed address.
 *
 * @ingroup themeable
 * @param $address
 *   Array. A single address with the following fields (generally, but it can have more):
 *   - 'street'       => A string representing the street
 *   - 'additional'   => A string for any additional portion of the street
 *   - 'city'         => A string for the city name
 *   - 'province'     => The standard postal abbreviation for the province
 *   - 'country'      => The two-letter ISO code for the country of the address (REQUIRED)
 *   - 'postal_code'  => The international postal code for the address
 * @param $hide
 *   Array (optional). The values are the address fields to suppress in the themed display.
 */
function theme_addresses($address, $hide = array()) {
  // Check if it have at least one field to be displayed.
  // If not, return '' and stop everything
  foreach ($hide as $field) {
    if (!empty($address[$field])) {
      unset($address[$field]);
    }
  }

  // If all fields are hidden, return ''
  if (empty($address)) {
    return '';
  }

  // Get the proper address format
  if (!empty($address['country'])
      and !$format_address = variable_get('addresses_format_'. $address['country'], '')) {

    // Load country specifice code .inc file if it exists.
    // For example, if country_code for U.S. == 'us', load 'addresses.us.inc'
    include_once drupal_get_path('module', 'addresses') .'/countries/'. $address['country'] .'.inc';

    // If the country has an preset address format
    $function = 'addresses_address_format_'. $address['country'];
    if (function_exists($function)) {
      $format_address = $function();
      variable_set('addresses_format_'. $address['country'], $format_address);
    }
  }

  // If still the proper address format, use the United States format
  if (empty($format_address) and !$format_address = variable_get('addresses_format_default', '')) {
    include_once drupal_get_path('module', 'addresses') .'/countries/us.inc';
    $format_address = addresses_address_format_us();
    variable_set('addresses_format_default', $format_address);
  }

  // Call token module to replace all tokens to their right value. Also,
  // use 'adr' microformat
  $format_address = "<dl class=\"adr\">\n".
    token_replace($format_address, 'addresses_adr', $address, '!', '') ."\n</dl>";

  // Besides being the Drupal Address info,
  // its possible to be used by hCard and VCard (if a address name was provided)
  $format_address = "<div class=\"vcard\">\n".
    token_replace($format_address, 'addresses_general', $address, '!', '') ."\n</div>";

  // Replace the new lines for HTML line breaks AND remove
  // all empty lines
  $format_address = explode("\n", $format_address);
  foreach (array_keys($format_address) as $line) {
    $format_address[$line] = trim($format_address[$line]);
    if (empty($format_address[$line])) {
      unset($format_address[$line]);
    }
  }
  $format_address = implode('<br/>', $format_address);

  // Add the CCS
  drupal_add_css(drupal_get_path('module', 'addresses') .'/addresses.css');

  return $format_address;
}

/**
 * Print the field City.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_city($fields) {
  return '<dt>'. t('City') .': </dt><dd class="city locality">'. $fields['city'] .'</dd>';
}

/**
 * Print the field Street.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_street($fields) {
  return '<dt>'. t('Address') .': </dt><dd class="street-address">'. $fields['street'] .'</dd>';
}

/**
 * Print the field Additional.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_additional($fields) {
  return '<dt>'. t('Additional') .': </dt><dd class="extended-address">'. $fields['additional'] .'</dd>';
}

/**
 * Print the field Country 3-digit code.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_country_name($fields) {
  $countries = _addresses_country_get();
  return '<dt>'. t('Country') .': </dt><dd class="country-name">'. $countries[$fields['country']] .'</dd>';
}

/**
 * Print the field Country 2-digit code.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_country_code2($fields) {
  $countries = _addresses_country_get();
  return '<dt>'. t('Country') .': </dt><dd><abbr class="country-name" title="'.
    $countries[$fields['country']] .'">'. strtoupper($fields['country']) .'</abbr></dd>';
}

/**
 * Print the field Country name.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_country_code3($fields) {
  $countries = _addresses_country_get();
  $country_code3 = _addresses_country_get_code3();
  return '<dt>'. t('Country') .': </dt><dd><abbr class="country-name" title="'.
    $countries[$fields['country']] .'">'. strtoupper($country_code3[$fields['country']]) .'</abbr></dd>';
}

/**
 * Print the field Postal Code.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_postal_code($fields) {
  return '<dt>'. t('Postal Code') .': </dt><dd class="region">'. $fields['postal_code'] .'</dd>';
}

/**
 * Print the field Province name.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_province_name($fields) {
  $provinces = _addresses_province_get($fields['country']);
  return '<dt>'. t('Province') .': </dt><dd class="region">'. $provinces[$fields['province']] .'</dd>';
}

/**
 * Print the field Province code.
 *
 * @param $fields
 *   Array. All field values
 * @ingroup themeable
 */
function theme_addresses_field_province_code($fields) {
    $provinces = _addresses_province_get($fields['country']);
    return '<dt>'. t('Province') .': </dt><dd><abbr class="region" title="'.
      $provinces[$fields['province']] .'">'. strtoupper($fields['province']) .'</abbr></dd>';
}

/**
 * Create a single line address. Usefull for some labels.
 *
 * @param $address
 *   Array. The address parts. see theme_address()
 * @return
 *   String. The single line address
 * @ingroup themeable
 */
function theme_addresses_singleline($address) {
  // Check if its a valied address
  if (empty($address)) {
    return '';
  }

  $address = '';

  // Add the streets
  if (!empty($address['street'])) {
    $address .= $address['street'];
  }

  // Add the city
  if (!empty($address['city'])) {
    if (!empty($address['street'])) {
      $address .= ', ';
    }
    $address .= $address['city'];
  }

  // Add the state / province
  if (!empty($address['province'])) {
    if (!empty($address['street']) or !empty($address['city'])) {
      $address .= ', ';
    }
    $address .= $address['province'];
  }

  // Add the Postal code
  if (!empty($address['postal_code'])) {
    if (!empty($address)) {
      $address .= ' ';
    }
    $address .= $address['postal_code'];
  }

  // Add the country
  if (!empty($address['country'])) {
    $address .= ', '. $address['country'];
  }

  return $address;
}
