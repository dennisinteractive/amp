<?php
require_once 'MacroHelper.php';
require_once 'interfaces/FormatHelper.php';

class VendorHelper implements FormatHelper{
  public static function format($vendors) {
    $formatted = array();
    for($i= 0; $i < count($vendors); $i++) {
      $formatted = array($vendors[$i]['vendor_name'] => MacroHelper::format($vendors[$i]['macros']));
    }
    return $formatted;
  }
}
