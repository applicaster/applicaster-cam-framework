Pod::Spec.new do |s|
  s.name         = 'CAM'
  s.version      = '2.0.2'
  s.summary      = 'Content Access Manager framework'
  s.license      = 'MIT'
  s.homepage     = 'https://github.com/applicaster/applicaster-cam-framework'
  s.author       = {"Brel Egor" => "ebrel@applicaster.com"}
  s.ios.deployment_target = '10.0'
  s.swift_version = '5.1'
  s.source       = { :git => "https://github.com/applicaster/applicaster-cam-framework", :tag => 'ios-' + s.version.to_s }
  s.resources = 'iOS/CAM/**/*.{xib,nib,storyboard}'
  s.source_files = 'iOS/CAM/**/*.{swift,h,m}'
  s.requires_arc = true

  s.dependency 'ZappPlugins', '>= 11.1.2'
  s.dependency 'ApplicasterIAP'
end
