;  Copyright (C) 2002 Regents of the University of Michigan, 
;  portions used with permission 
;  For more information, see http://csem.engin.umich.edu/tools/swmf
;^CFG COPYRIGHT UM
pro set_device, psfile, port=port, land=land, square=square, eps=eps, $
                psfont=psfont, xratio=xratio, yratio=yratio

  ; Parameter defaults and conversions

  if not keyword_set(psfile) then psfile = 'idl.ps'
  common SETDEVICE, NameFile
  NameFile = psfile

  orientation = 'normal'
  if keyword_set(land)   then orientation='land'
  if keyword_set(port)   then orientation='port'
  if keyword_set(square) then orientation='square'

  if not keyword_set(xratio) then xratio = 1.0
  if not keyword_set(yratio) then yratio = 1.0

  if n_elements(psfont) eq 0  then psfont = 28

  ; If file extension is .eps it is an EPS file for sure
  if stregex(NameFile,'.eps$',/b) then eps = 1

  ; Set sizes and offsets
  case (orientation) of
     'normal': begin
        xs   = 10*xratio
        ys   =  7*yratio
        xoff = 11*xratio - (11*xratio - xs)/1.5
        yoff = (8.5*yratio - ys)/2.0
        land=0
     end
     'land': begin
        xs   = 10*xratio
        ys   = 7*yratio
        xoff = (8.5*yratio-ys)/2.0
        yoff = 11*xratio-(11*xratio-xs)/1.5
        land=1
     end
     'port': begin
        xs = 7.5*xratio
        ys = 9.5*yratio
        xoff = (8.5*xratio-xs)/2.0
        yoff = (11*yratio-ys)/2.0
        land=0
     end
     'square': begin
        xs = 7.5*xratio
        ys = 7.5*yratio
        xoff = (8.5*xratio-xs)/2.0
        yoff = (8.5*yratio-ys)/2.0
        land=0
     end
  endcase

  set_plot, 'PS', /copy, /interpolate

  !p.font = 0

  case (psfont) of
       -1  : device, file = psfile, encapsulated=eps, /color, bits=8,         $
                /inches, landscape=land, xsize = xs, ysize = ys, $
               xoff = xoff, yoff = yoff

	0  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Courier 
	1  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Courier, /Bold 
    	2  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Courier, /Oblique 
	3  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Courier, /Bold, /Oblique
       	4  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Helvetica
      	5  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Helvetica, /Bold
    	6  : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Helvetica, /Oblique
       	8  : device, file = psfile, encapsulated=eps, /color, bits=8,         $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Helvetica, /Bold, /Oblique 
    	12 : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Avantgarde, /Book 
     	13 : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Avantgarde, /Book, /Oblique
	14 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Avantgarde, /Demi 
      	15 : device, file = psfile, encapsulated=eps, /color, bits=8,	      $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Avantgarde, /Demi, /Oblique
       	20 : device, file = psfile, encapsulated=eps, /color, bits=8, $
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Schoolbook
   	21 : device, file = psfile, encapsulated=eps, /color, bits=8,$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Schoolbook, /Bold
      	22 : device, file = psfile, encapsulated=eps, /color, bits=8,$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Schoolbook, /Italic
       	23 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Schoolbook, /Bold, /Italic 
	28 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Times, font_index=5
	29 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Times, /Bold
	30 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Times, /Italic
	31 : device, file = psfile, encapsulated=eps, /color, bits=8,	$
		/inches, landscape=land, xsize = xs, ysize = ys, $
		xoff = xoff, yoff = yoff,  $
		/Times, /Bold, /Italic

    endcase

  return

end

