# Script that synchronizes the local test data

$TestsInputDirectory = "tests\input"
$TestSet = "public"
$TestFiles = "ext2.E01 ext2.raw"
If (-Not (Test-Path "${TestsInputDirectory}\.libewf_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.libewf_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[ELels]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.libewf_legacy\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.pyewf_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.pyewf_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[ELels]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.pyewf_legacy\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfacquire"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfacquire" -ItemType "directory" | Out-Null
	Write-Output "*.[Rr][Aa][Ww]" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfacquire\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfacquire_optical"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfacquire_optical" -ItemType "directory" | Out-Null
	Write-Output "*.[Cc][Uu][Ee]" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfacquire_optical\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfacquirestream"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfacquirestream" -ItemType "directory" | Out-Null
	Write-Output "*.[Rr][Aa][Ww]" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfacquirestream\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfexport_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfexport_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[Ees]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfexport_legacy\glob"
	Write-Output "-fraw" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfexport_legacy\options"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfexport_logical_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfexport_logical_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[Ll]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfexport_logical_legacy\glob"
	Write-Output "-ffiles" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfexport_logical_legacy\options"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfexport_write"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfexport_write" -ItemType "directory" | Out-Null
	Write-Output "*.[Ees]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfexport_write\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfinfo"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfinfo_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[ELels]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfinfo_legacy\glob"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfinfo_logical_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfinfo_logical_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[Ll]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfinfo_logical_legacy\glob"
	Write-Output "-H" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfinfo_logical_legacy\options"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfverify_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfverify_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[Ees]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfverify_legacy\glob"
	Write-Output "-dmd5" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfverify_legacy\options"
}
If (-Not (Test-Path "${TestsInputDirectory}\.ewfverify_logical_legacy"))
{
	New-Item -Name "${TestsInputDirectory}\.ewfverify_logical_legacy" -ItemType "directory" | Out-Null
	Write-Output "*.[Ll]01" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfverify_logical_legacy\glob"
	Write-Output "-dmd5 -ffiles" | Out-File -Encoding ascii -FilePath "${TestsInputDirectory}\.ewfverify_logical_legacy\options"
}

If (-Not (Test-Path ${TestsInputDirectory}))
{
	New-Item -Name ${TestsInputDirectory} -ItemType "directory" | Out-Null
}
If (-Not (Test-Path "${TestsInputDirectory}\${TestSet}"))
{
	New-Item -Name "${TestsInputDirectory}\${TestSet}" -ItemType "directory" | Out-Null
}
ForEach ($TestFile in ${TestFiles} -split " ")
{
	$UrlTestFile = [System.Uri]::EscapeDataString("${TestFile}")
	$Url = "https://raw.githubusercontent.com/log2timeline/dfvfs/refs/heads/main/test_data/${UrlTestFile}"

	$ProgressPreference = 'SilentlyContinue'
	Invoke-WebRequest -Uri ${Url} -OutFile "${TestsInputDirectory}\${TestSet}\${TestFile}"
}
