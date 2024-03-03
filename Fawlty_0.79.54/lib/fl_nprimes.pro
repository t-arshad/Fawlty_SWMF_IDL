function fl_nprimes, n, primes=primes
    nn=long(n)
    max=max(nn)

    if ( max lt 2 ) then np=0l
    if ( max eq 2 ) then np=1l
    if ( max ge 3 ) then $
    begin
        sieve=replicate(1b,max+1l)
        sieve[0]=0b
        sieve[1]=0b
        sieve[4l:*:2l]=0b

        p=3l
        np=2l
        while ( 2l*p le max ) do $
        begin
            sieve[2l*p:*:p]=0 
            for j=p+2l,max,2l do $
                if ( sieve[j] ) then $
                begin
                    p=j & np=np+1l & break
                endif
        end
    end

    count=0
    if ( arg_present(primes) ) then primes=where(sieve, count)

    nelem=size(nn,/n_elements)
    if ( nelem eq 1 ) then $
    begin
        if ( max ge 3 ) then $
            begin
                if ( count gt 0 ) then np=count $
                else $
                    for j=p+2l,max,2l do $
                        if ( sieve[j] ) then np++
            end
        nn[0]=np
        return, nn
    end

    res=lonarr(nelem)
    index=sort(nn)
    beg=3l
    np=1l
    for k=0l,nelem-1l do $
    begin
        ind=index[k]
        val=nn[ind]
        if ( val lt 2 ) then res[ind]=0l
        if ( val eq 2 ) then res[ind]=1l
        if ( val ge 3 ) then $
            begin
            if ( val mod 2 eq 0 ) then val--
                for j=beg,val,2l do $
                    if ( sieve[j] ) then np++
                res[ind]=np
                beg=val+2
            end
    end
    return, res
end
