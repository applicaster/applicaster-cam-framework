#!/bin/bash +x

output_plist_file_name="Settings.bundle/Root.plist"
plist_buddy_path="/usr/libexec/PlistBuddy"

APPVERSION="`\"${plist_buddy_path}\" -c \"Print :CFBundleVersion\" \"Info.plist\"`"
CLIENTDEMOBOOL="`\"${plist_buddy_path}\" -c \"Print :APClientDemoApp\" \"ApplicasterSettings.plist\"`"
APPSORTVERSION="`\"${plist_buddy_path}\" -c \"Print :CFBundleShortVersionString\" \"Info.plist\"`"

if ! [ "$CONFIGURATION" = "Debug" ] ; then
    "${plist_buddy_path}" -c "Add :StringsTable string 'Root'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers array" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0 dict" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0:Type string 'PSGroupSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0:Title string 'About'" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Type string 'PSTitleValueSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Title string 'Version:'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Key string 'appVersion'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:DefaultValue string '${APPSORTVERSION} ($APPVERSION)'" "${output_plist_file_name}"
fi

if [ "$CONFIGURATION" = "Debug" ] ; then
    if ! [ -n "$CLIENTDEMOBOOL" ]; then
        CLIENTDEMOBOOL=false
    fi

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers array" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0:Title string 'About'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0:Type string 'PSGroupSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:0:FooterText string 'Changing the current servers will close the application. This option available only in debug mode'" "${output_plist_file_name}"


    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Type string 'PSTitleValueSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Title string 'Version'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:DefaultValue string '$APPSORTVERSION ($APPVERSION)'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:1:Key string 'appVersion'" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:2 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:2:Title string 'Applicaster Server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:2:Type string 'PSGroupSpecifier'" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:key string 'Titles'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles array" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:0 string 'Production'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:1 string 'Demo'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values array" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:0 string 'production_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:1 string 'demo_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Title string 'Server Type'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Type string 'PSMultiValueSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Key string 'server_type'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:DefaultValue string 'production_server'" "${output_plist_file_name}"

    if ! $CLIENTDEMOBOOL ; then
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:3 string 'Development'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:4 string 'QA'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:5 string 'Test'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:6 string 'Server'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Titles:7 string 'Custom'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:3 string 'development_server'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:4 string 'qa_server'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:5 string 'test_server'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:6 string 'server_server'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:3:Values:7 string 'custom_server'" "${output_plist_file_name}"

        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:4 dict" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:4:Type string 'PSTextFieldSpecifier'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:4:Title string 'Custom Address'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:4:Key string 'custom_server_textfield'" "${output_plist_file_name}"
        "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:4:DefaultValue string '127.0.0.1'" "${output_plist_file_name}"
    fi

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:5 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:5:Title string 'Applicaster Components Server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:5:Type string 'PSGroupSpecifier'" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:key string 'Titles'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles array" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:0 string 'Production'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:1 string 'Demo'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values array" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:0 string 'components_production_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:1 string 'components_demo_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Title string 'Server Type'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Type string 'PSMultiValueSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Key string 'components_server_type'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:DefaultValue string 'components_production_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:2 string 'Staging'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:3 string 'Development'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:4 string 'Local'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Titles:5 string 'Custom'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:2 string 'components_staging_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:3 string 'components_development_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:4 string 'components_local_server'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:6:Values:5 string 'components_custom_branch'" "${output_plist_file_name}"

    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:7 dict" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:7:Type string 'PSTextFieldSpecifier'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:7:Title string 'Custom'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:7:Key string 'components_custom_branch_textfield'" "${output_plist_file_name}"
    "${plist_buddy_path}" -c "Add :PreferenceSpecifiers:7:DefaultValue string ''" "${output_plist_file_name}"
fi