<?php

/**
 * @file Serializes the object to a value that can be serialized natively by json_encode().
 */

/**
 * Implements JsonSerializable Interface.
 */
class RealTimeConfiguration implements JsonSerializable {
  private $vendors;
  private $urls;
  private $timeout;
  
  /**
   * Constructor, take params & formats them.
   * 
   * @param type $vendors
   * @param type $urls
   * @param type $timeout
   */
  public function __construct($vendors, $urls, $timeout) {
    $this->vendors = $this->formatVendor($vendors);
    $this->urls = $this->formatUrls($urls);
    $this->timeout = $timeout;
  }

  /**
   * Formats the vendor elements to match the expected rtc output.
   *
   * @param mixed $vendors
   *
   * @return type array
   */
  private function formatVendor($vendors) {
    $formatted = array();
    for ($i = 0; $i < count($vendors); $i++) {
      $formatted[$vendors[$i]['vendor_name']] = $this->formatMacros($vendors[$i]['macros']);
    }

    return $formatted;
  }

  /**
   * Formats the macros into the required format to be used in the vendor array.
   *
   * @param mixed $macros
   *
   * @return type array
   */
  private function formatMacros($macros) {
    $formatted = array();
    for ($i = 0; $i < count($macros); $i++) {
      $formatted[$macros[$i]['macro']] = $macros[$i]['value'];
    }

    return $formatted;
  }

  /**
   * Formats the urls elements, to match expected rtc output.
   *
   * @param mixed $urls
   *
   * @return type array
   */
  private function formatUrls($urls) {
    $formatted = array();
    for ($i = 0; $i < count($urls); $i++) {
      if (!empty($urls[$i]['rtc_error_url'])) {
        $formatted[] = (object) [
          'url' => $urls[$i]['rtc_url'],
          'errorReportingUrl' => $urls[$i]['rtc_error_url'],
        ];
      }
      else {
        $formatted[] = $urls[$i]['rtc_url'];
      }
    }

    return $formatted;
  }

  /**
   *
   * @return type json object
   */
  public function jsonSerialize() {
    return array(
      'vendors' => $this->vendors,
      'urls' => $this->urls,
      'timeoutMillis' => $this->timeout,
    );
  }

}
