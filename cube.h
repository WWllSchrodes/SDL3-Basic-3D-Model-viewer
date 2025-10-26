#pragma once

const uint16_t Cube_vert_ind[12 * 2] =	// 12 Pairs of indices (points of Cube)
{
0,1,	// Front Top Left		-> Front Top Right
1,2,	// Front Top Right		-> Front Bottom Right
2,3,	// Front Bottom Right	-> Front Bottom Left
3,0,	// Front Bottom Left	-> Front Top Left
4,5,	// Back Top Left		-> Back Top Right
5,6,	// Back Top Right		-> Back Bottom Right
6,7,	// Back Bottom Right	-> Back Bottom Left
7,4,	// Back Bottom Left		-> Back Top Left
// Below we join the Front face of the Cube to the Back face of the Cube
0,4,	// Front Top Left		-> Back Top Left
1,5,	// Front Top Right		-> Back Top Right
2,6,	// Front Bottom Right	-> Back Bottom Right
3,7,	// Front Bottom Left	-> Back Bottom Left
};
