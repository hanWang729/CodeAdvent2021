import sys, re

ss = [ s.splitlines() for s in sys.stdin.read().split( "\n\n" ) ]

g = { ( x, y ): c
      for y, r in enumerate( ss[ 0 ] )
      for x, c in enumerate( r )
      if c in ".#" }
d = re.findall( "L|R|\d+", ss[ 1 ][ 0 ] )

x0, y0 = min( x for x, y in g.keys() ), min( y for x, y in g.keys() )
x1, y1 = max( x for x, y in g.keys() ), max( y for x, y in g.keys() )

y, x = min( ( k[ 1 ], k[ 0 ] ) for k, v in g.items() if v == '.' )
f = 0

p = {}
for i in d:
    if i == 'L':
        f = ( f - 1 ) % 4
    elif i == 'R':
        f = ( f + 1 ) % 4
    else:
        for s in range( int( i ) ):
            dx = [ 1, 0, -1, 0 ][ f ]
            dy = [ 0, 1, 0, -1 ][ f ]
            nx, ny, nf = x + dx, y + dy, f
            if ( nx, ny ) not in g:
                ox, oy =  x // 50,  y // 50
                fx, fy = nx // 50, ny // 50
                rx, ry = nx  % 50, ny  % 50
                if ( ox, oy ) == ( 1, 0 ):
                    if ( fx, fy ) == ( 1, -1 ):
                        fx, fy = 0, 3
                        rx, ry = 49 - ry, rx
                        nf = 0
                    if ( fx, fy ) == ( 0, 0 ):
                        fx, fy = 0, 2
                        rx, ry = 49 - rx, 49 - ry
                        nf = 0
                elif ( ox, oy ) == ( 2, 0 ):
                    if ( fx, fy ) == ( 2, -1 ):
                        fx, fy = 0, 3
                        nf = f
                    elif ( fx, fy ) == ( 3, 0 ):
                        fx, fy = 1, 2
                        rx, ry = 49 - rx, 49 - ry
                        nf = 2
                    elif ( fx, fy ) == ( 2, 1 ):
                        fx, fy = 1, 1
                        rx, ry = 49 - ry, rx
                        nf = 2
                elif ( ox, oy ) == ( 1, 1 ):
                    if ( fx, fy ) == ( 0, 1 ):
                        fx, fy = 0, 2
                        rx, ry = ry, 49 - rx
                        nf = 1
                    elif ( fx, fy ) == ( 2, 1 ):
                        fx, fy = 2, 0
                        rx, ry = ry, 49 - rx
                        nf = 3
                elif ( ox, oy ) == ( 0, 2 ):
                    if ( fx, fy ) == ( 0, 1 ):
                        fx, fy = 1, 1
                        rx, ry = 49 - ry, rx
                        nf = 0
                    elif ( fx, fy ) == ( -1, 2 ):
                        fx, fy = 1, 0
                        rx, ry = 49 - rx, 49 - ry
                        nf = 0
                elif ( ox, oy ) == ( 1, 2 ):
                    if ( fx, fy ) == ( 2, 2 ):
                        fx, fy = 2, 0
                        rx, ry = 49 - rx, 49 - ry
                        nf = 2
                    elif ( fx, fy ) == ( 1, 3 ):
                        fx, fy = 0, 3
                        rx, ry = 49 - ry, rx
                        nf = 2
                elif ( ox, oy ) == ( 0, 3 ):
                    if ( fx, fy ) == ( -1, 3 ):
                        fx, fy = 1, 0
                        rx, ry = ry, 49 - rx
                        nf = 1
                    elif ( fx, fy ) == ( 1, 3 ):
                        fx, fy = 1, 2
                        rx, ry = ry, 49 - rx
                        nf = 3
                    elif ( fx, fy ) == ( 0, 4 ):
                        fx, fy = 2, 0
                        nf = f
                nx, ny = fx * 50 + rx, fy * 50 + ry
            if g[ ( nx, ny ) ] == '.':
                x, y, f = nx, ny, nf
                p[ ( x, y ) ] = { 0: '>', 1: 'v', 2: '<', 3: '^' }[ f ]
            elif g[ ( nx, ny ) ] == '#':
                break

print( 1000 * ( y + 1 ) + 4 * ( x + 1 ) + f )
