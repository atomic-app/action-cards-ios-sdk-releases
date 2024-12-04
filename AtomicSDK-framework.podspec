Pod::Spec.new do |s|
s.name                = 'AtomicSDK-framework'
s.version             = '23.4.14'
s.summary             = 'Atomic SDK for iOS, distributed as a fat framework.'
s.license             = { :type => 'Commercial', :text => ' ' }
s.authors             = 'Atomic.io Limited'
s.homepage            = 'https://atomic.io/'
s.description         = 'The Atomic SDK for integrating Atomic into your app. Supports iOS 12.0+.'
s.requires_arc        = true
s.source              = { :git => 'https://github.com/atomic-app/action-cards-ios-sdk-releases.git', :tag => '23.4.14' }
s.platform            = :ios, '12.0'
s.preserve_paths      = 'iOS/AtomicSDK.framework'
s.public_header_files = 'iOS/AtomicSDK.framework/Headers/*.h'
s.source_files        = 'iOS/AtomicSDK.framework/Headers/*.h'
s.vendored_frameworks = 'iOS/AtomicSDK.framework'
end
