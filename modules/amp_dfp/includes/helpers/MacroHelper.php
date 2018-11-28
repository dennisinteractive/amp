<?php
require_once 'interfaces/FormatHelper.php';

class MacroHelper implements FormatHelper{
   public static function format($macros) {
    $formatted = array();
    for($i= 0; $i < count($macros); $i++) {
      $formatted = array($macros[$i]['macro'] => $macros[$i]['value']);
    }
    return $formatted;
  }
}
