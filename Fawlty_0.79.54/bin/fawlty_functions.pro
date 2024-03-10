pro make_movie,quality

;quality: 0 will go .ps -> .png -> .mov   - High Quality
;quality: 1 will go .png -> .mov   - Low Quality
common animate_param



spawn,'mkdir Movie'
cd, 'Movie' 
spawn, 'rm -rf *'
cd, '..'
IF (quality EQ 0) THEN BEGIN 
savemovie='ps'
END
IF (quality EQ 1) THEN BEGIN 
savemovie='png'
END
animate_data
savemovie='n'
cd, 'Movie'
spawn, 'cp ~/Apps/Fawlty*/Fawlty*/bin/conv_ps_mp4 ./'
spawn, 'gnome-terminal -- ./conv_ps_mp4'
spawn, 'rm -rf conv_ps_mp4'
cd, '..'
spawn, 'echo '
spawn, 'echo '
spawn, 'echo '
spawn, 'echo '
spawn, 'echo ----------------------------------------'
spawn, 'echo Check other window for completion status'
spawn, 'echo ----------------------------------------'
spawn, 'echo '
spawn, 'echo '
spawn, 'echo '
spawn,'uname',uname
if strpos(uname[0],'IRIX')  ge 0 then device,retain=2,pseudo_color=8
if strpos(uname[0],'Linux') ge 0 then device,decompose=0,true=24,retain=2
if strpos(uname[0],'Darwin') ge 0 then device,decompose=0,true=24,retain=2

end
