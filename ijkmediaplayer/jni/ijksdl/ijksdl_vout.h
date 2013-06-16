/*****************************************************************************
 * ijksdl_vout.h
 *****************************************************************************
 *
 * copyright (c) 2013 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of ijkPlayer.
 *
 * ijkPlayer is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * ijkPlayer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with ijkPlayer; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef IJKSDL__IJKSDL_VOUT_H
#define IJKSDL__IJKSDL_VOUT_H

#include "ijksdl_stdinc.h"
#include "ijksdl_mutex.h"
#include "ijksdl_video.h"

/* bpp=12, 8 bit Y plane followed by 8 bit 2x2 subsampled V and U planes.*/
#define SDL_FOURCC_PIX__YV12        0x32315659

typedef struct SDL_VoutOverlay_Opaque SDL_VoutOverlay_Opaque;
typedef struct SDL_VoutOverlay SDL_VoutOverlay;
typedef struct SDL_VoutOverlay {
    int w; /**< Read-only */
    int h; /**< Read-only */
    Uint32 format; /**< Read-only */
    int planes; /**< Read-only */
    Uint16 *pitches; /**< Read-only */
    Uint8 **pixels; /**< Read-write */

    void *opaque;
    void (*free_l)(SDL_VoutOverlay *overlay);
} SDL_VoutOverlay;

typedef struct SDL_VoutSurface_Opaque SDL_VoutSurface_Opaque;
typedef struct SDL_VoutSurface SDL_VoutSurface;
typedef struct SDL_VoutSurface {
    int w;
    int h;
    Uint32 format; /* fourcc number */

    SDL_VoutSurface_Opaque *opaque;
} SDL_VoutSurface;

typedef struct SDL_Vout_Opaque SDL_Vout_Opaque;
typedef struct SDL_Vout SDL_Vout;
typedef struct SDL_Vout {
    SDL_mutex *mutex;

    SDL_Vout_Opaque *opaque;
    void (*free_l)(SDL_Vout *vout);
    SDL_VoutSurface *(*set_video_mode)(SDL_Vout *vout, int w, int h, int bpp, Uint32 flags);
} SDL_Vout;

void SDL_VoutFree(SDL_Vout *vout);
SDL_VoutSurface *SDL_VoutSetVideoMode(SDL_Vout *vout, int w, int h, int bpp, Uint32 flags);

void SDL_VouFreeOverlay(SDL_VoutOverlay *overlay);

#endif
