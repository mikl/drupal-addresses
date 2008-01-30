<?php
// $Id$

// Brazil

/**
 * Implementation of hook_province_list().
 *
 * Its a hook from Addresses module to list all
 * states/provinces/teritories of a given contry
 *
 * @return
 *   Array. states where the keys are the state
 *   code and the value is the state name
 */
functionaddresses_province_list_br() {
  return array(
    'AC' => t('Acre'),
    'AL' => t('Alagoas'),
    'AM' => t('Amazonas'),
    'AP' => t('Amapa'),
    'BA' => t('Bahia'),
    'CE' => t('Ceara'),
    'DF' => t('Distrito Federal'),
    'ES' => t('Espirito Santo'),
    'GO' => t('Goias'),
    'MA' => t('Maranhao'),
    'MG' => t('Minas Gerais'),
    'MS' => t('Mato Grosso do Sul'),
    'MT' => t('Mato Grosso'),
    'PA' => t('Para'),
    'PB' => t('Paraiba'),
    'PE' => t('Pernambuco'),
    'PI' => t('Piaui'),
    'PR' => t('Parana'),
    'RJ' => t('Rio de Janeiro'),
    'RN' => t('Rio Grande do Norte'),
    'RO' => t('Rondonia'),
    'RR' => t('Roraima'),
    'RS' => t('Rio Grande do Sul'),
    'SC' => t('Santa Catarina'),
    'SE' => t('Sergipe'),
    'SP' => t('Sao Paulo'),
    'TO' => t('Tocantins')
  );
}
