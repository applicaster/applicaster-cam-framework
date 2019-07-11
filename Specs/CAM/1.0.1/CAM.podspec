Pod::Spec.new do |s|
  s.name         = 'CAM'
  s.version      = '1.0.1'
  s.summary      = 'Content Access Manager framework'
  s.license      = 'MIT'
  s.homepage     = 'https://github.com/applicaster/applicaster-cam-framework'
  s.author       = {"Brel Egor" => "brel@scand.com"}
  s.ios.deployment_target = '10.0'
  s.swift_version = '4.2'
  s.source       = { :git => "https://github.com/applicaster/applicaster-cam-framework", :tag => 'ios-' + s.version.to_s }
  s.resources = 'iOS/CAM/**/*.{xib,nib,storyboard}'
  s.source_files = 'iOS/CAM/**/*.{swift,h,m}'
  s.requires_arc = true

  s.dependency 'ZappPlugins'  
  s.dependency 'ApplicasterIAP'
end
