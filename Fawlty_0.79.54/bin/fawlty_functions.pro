pro save_gif_fawlty

common animate_param

spawn,'mkdir Movie'
cd, 'Movie' 
spawn, 'rm -rf *.ps'
spawn, 'rm -rf *.gif'
spawn, 'rm -rf *.pdf'
cd, '..'  
savemovie='ps'
animate_data
savemovie='n'
cd, 'Movie'
print,''
print,'------------------------'
print,'Merging PostScript Files'
spawn, 'convert ./*.ps -rotate 270 ./PS.ps'
spawn,'mv ./PS.ps ./PS.pss'
spawn,'rm -rf *.ps'
spawn,'mv ./PS.pss ./PS.ps'
print,''
print,'------------------------'
print,'Converting Merged PostScript File to GIF'
spawn, 'convert ./PS.ps ./GIF.gif'
;print,''
;print,'------------------------'
;print,'Converting Merged PostScript File to PDF'
;spawn, 'convert ./PS.ps ./PDF.pdf'
cd, '..'
print,''
print,'----'
print,'Done'
print,'----'
print,''
spawn,'uname',uname
if strpos(uname[0],'IRIX')  ge 0 then device,retain=2,pseudo_color=8
if strpos(uname[0],'Linux') ge 0 then device,decompose=0,true=24,retain=2
if strpos(uname[0],'Darwin') ge 0 then device,decompose=0,true=24,retain=2

end
