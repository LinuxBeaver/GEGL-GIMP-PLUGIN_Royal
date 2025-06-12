/* This file is an image processing operation for GEGL
 *
 * GEGL is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * GEGL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with GEGL; if not, see <https://www.gnu.org/licenses/>.
 *
 * Credit to Øyvind Kolås (pippin) for major GEGL contributions
 * 2024 Beaver, Royal Text

Syntax to recreate plugin here


color-overlay value=#f95dff gaussian-blur std-dev-x=3 std-dev-y=1




id=1 screen  aux=[ ref=1  emboss  type=bumpmap azimuth=70  elevation=53 depth=23 opacity value=4.5  ]
median-blur radius=0 abyss-policy=none

id=2
median-blur radius=0 abyss-policy=none
id=3 over aux=[ ref=3 lb:glassovertext ]
dst-over aux=[  ref=2  median-blur radius=10 alpha-percentile=100 abyss-policy=none ]
hue-chroma hue=-0
dst-over aux=[  ref=2  median-blur radius=20 alpha-percentile=100 abyss-policy=none

hue-chroma hue=49 lightness=-3 lb:metallic guichange=colormetal color=#ffe600 solar1=6.2 ]
id=4 gimp:layer-mode layer-mode=luminance  opacity=0.5 aux=[ ref=4 edge amount=3.4 ]

bloom strength=20
lb:threshold-alpha
levels in-low=0.11


--end of syntax

Fun Fact, this plugin has a graph very similar to Glossy Balloon at the beginning but with heavily modifications in the middle and afterward. It does not depend on Glossy Balloon.
 */

#include "config.h"
#include <glib/gi18n-lib.h>

#ifdef GEGL_PROPERTIES


property_int (hue, _("Rotate color of bevel"), 0)
    description (_("The bevel's color can be controlled by a limited hue rotation, due to technical limitations the hue rotation cannot go all the way"))
    value_range (-45, 45)
    ui_meta ("unit", "degree")


property_int (outline_hue, _("Rotate color of bevel outline"), 0)
    description (_("The bevel outline's color can be controlled by a limited hue rotation, due to technical limitations the hue rotation cannot go all the way"))
    value_range (-45, 45)
    ui_meta ("unit", "degree")

property_double (azimuth, _("Azimuth of everything"), 67.0)
    description (_("The bevel and bevel outline's light angle (degrees)"))
    value_range (30, 90)
    ui_meta ("unit", "degree")

property_double (elevation, _("Elevation of everything"), 40.0)
    description (_("The bevel and bevel outline's elevation angle (degrees)"))
    value_range (7, 90)
    ui_meta ("unit", "degree")

property_int (depth, _("Depth/detail of everything"), 24)
    description (_("Brings out depth and or detail of both the bevel and bevel outline"))
    value_range (1, 100)

property_double (glass_azimuth, _("Glass light rotation"), 30.0)
    description (_("Glass light rotation (azimuth)"))
    value_range (0, 360)
    ui_meta ("unit", "degree")
    ui_meta ("direction", "ccw")
  ui_steps      (0.5, 0.50)

property_double (enhance, _("Shine enhancer"), 3.0)
    description (_("Edge detect on the luminance blend mode to enhance the shine. At low values this will make the bevel dark"))
    value_range (0.0, 6.0)
    ui_meta ("unit", "degree")

property_int (bloom, _("Bloom light"), 20)
    description (_("The bloom filter's strength function to give the text style a lighting and glow effect"))
    value_range (10.0, 40.0)


property_int (outline_size, _("Outline size"), 24)
    description (_("Size of the bevel outline. At 0 and other very low values the outline bevel is seemingly removed"))
    value_range (0, 40)


property_double (tail, _("Extrusion length"), 0.0)
    description (_("Length of the extrusion. At 0.0 the extrusion is seemingly removed"))
    value_range (0.0, 0.020)
    ui_range    (0.0, 0.020)
    ui_gamma    (2.0)

property_double (x, _("Horizontal extrusion control"), 0.0)
    value_range (-0.5, 0.5)
    ui_range    (-0.5, 0.5)
    description(_("Horizontal movability of the extrusion"))

property_double (y, _("Vertical extrusion control"), 0.0)
    value_range (-0.5, 0.5)
    ui_range    (-0.5, 0.5)
    description(_("Vertical movability of the extrusion"))

#else

#define GEGL_OP_META
#define GEGL_OP_NAME     royal
#define GEGL_OP_C_SOURCE royal.c

#include "gegl-op.h"

static void attach (GeglOperation *operation)
{
  GeglNode *gegl = operation->node;
  GeglColor *basecolor = gegl_color_new ("#f95dff");


    GeglNode *input    = gegl_node_get_input_proxy (gegl, "input");
    GeglNode *output   = gegl_node_get_output_proxy (gegl, "output");


    GeglNode *hcolor    = gegl_node_new_child (gegl,
                                  "operation", "gegl:color-overlay", "value", basecolor,
                                  NULL);

    GeglNode *unequalblur    = gegl_node_new_child (gegl,
                                  "operation", "gegl:gaussian-blur", "std-dev-x", 3.0, "std-dev-y", 1.0, "abyss-policy", 0, "clip-extent", 0,
                                  NULL);

    GeglNode *emboss    = gegl_node_new_child (gegl,
                                  "operation", "gegl:emboss", "type", 1,
                                  NULL);

    GeglNode *metallic    = gegl_node_new_child (gegl,
                                  "operation", "lb:metallic", "guichange", 1, "solar1", 6.0,
                                  NULL);

    GeglNode *idref1    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

    GeglNode *idref2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

    GeglNode *idref3    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

    GeglNode *idref4    = gegl_node_new_child (gegl,
                                  "operation", "gegl:nop",
                                  NULL);

    GeglNode *behind1    = gegl_node_new_child (gegl,
                                  "operation", "gegl:dst-over",
                                  NULL);

    GeglNode *behind2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:dst-over",
                                  NULL);

    GeglNode *screen    = gegl_node_new_child (gegl,
                                  "operation", "gegl:screen",
                                  NULL);

    GeglNode *bloom    = gegl_node_new_child (gegl,
                                  "operation", "gegl:bloom", "strength", 20.0,
                                  NULL);

    GeglNode *lightweak    = gegl_node_new_child (gegl,
                                  "operation", "gegl:levels", "in-low", 0.11,
                                  NULL);

    GeglNode *ta    = gegl_node_new_child (gegl,
                                  "operation", "lb:threshold-alpha",
                                  NULL);

    GeglNode *normal   = gegl_node_new_child (gegl,
                                  "operation", "gegl:over",
                                  NULL);

    GeglNode *edge   = gegl_node_new_child (gegl,
                                  "operation", "gegl:edge", "amount", 3.0,
                                  NULL);

    GeglNode *glassoverlay    = gegl_node_new_child (gegl,
                                  "operation", "lb:glassovertext",
                                  NULL);

    GeglNode *opacity    = gegl_node_new_child (gegl,
                                  "operation", "gegl:opacity", "value", 4.5,
                                  NULL);

    GeglNode *fix1    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0, "abyss-policy", 0,
                                  NULL);

    GeglNode *fix2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 0,  "abyss-policy", 0,
                                  NULL);

    GeglNode *grow1    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 10, "alpha-percentile", 100.0, "abyss-policy", 0,
                                  NULL);

    GeglNode *grow2    = gegl_node_new_child (gegl,
                                  "operation", "gegl:median-blur", "radius", 20, "alpha-percentile", 100.0, "abyss-policy", 0,
                                  NULL);

    GeglNode *luma    = gegl_node_new_child (gegl,
                                  "operation", "gimp:layer-mode", "layer-mode", 56, "opacity", 0.5,
                                  NULL);

    GeglNode *extrusion   = gegl_node_new_child (gegl,
                                  "operation", "lb:extrusion",
                                  NULL);

    GeglNode *hue1   = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

    GeglNode *hue2   = gegl_node_new_child (gegl,
                                  "operation", "gegl:hue-chroma",
                                  NULL);

  gegl_node_link_many (input, hcolor, unequalblur, idref1, screen, fix1, idref2, fix2, idref3, normal, behind1, hue1, behind2, idref4, luma, bloom, ta, lightweak, extrusion, output, NULL);
/*Screen with emboss is here*/
  gegl_node_connect (screen, "aux", opacity, "output");
  gegl_node_link_many (idref1, emboss, opacity, NULL);
/*Glass Overlay on normal blend mode is here*/
  gegl_node_link_many (idref3, glassoverlay, NULL);
  gegl_node_connect (normal, "aux", glassoverlay, "output");
/*The behind blend mode idref2 with median blur is here*/
  gegl_node_connect (behind1, "aux", grow1, "output");
  gegl_node_connect (behind2, "aux", hue2, "output");
  gegl_node_link_many (idref2, grow1,  NULL);
  gegl_node_link_many (idref2, grow2, metallic, hue2, NULL);
/*Luminance with edge detect*/
  gegl_node_connect (luma, "aux", edge, "output");
  gegl_node_link_many (idref4, edge, NULL);

  gegl_operation_meta_redirect (operation, "bloom",  bloom, "strength");
  gegl_operation_meta_redirect (operation, "enhance",  edge, "amount");
  gegl_operation_meta_redirect (operation, "outline_size",  grow2, "radius");
  gegl_operation_meta_redirect (operation, "glass_azimuth",  glassoverlay, "azimuth");
  gegl_operation_meta_redirect (operation, "azimuth",  emboss, "azimuth");
  gegl_operation_meta_redirect (operation, "depth",  emboss, "depth");
  gegl_operation_meta_redirect (operation, "elevation",  emboss, "elevation");
  gegl_operation_meta_redirect (operation, "tail",  extrusion, "factor");
  gegl_operation_meta_redirect (operation, "x",  extrusion, "center_x");
  gegl_operation_meta_redirect (operation, "y",  extrusion, "center_y");
  gegl_operation_meta_redirect (operation, "hue",  hue1, "hue");
  gegl_operation_meta_redirect (operation, "outline_hue",  hue2, "hue");
}

static void
gegl_op_class_init (GeglOpClass *klass)
{
  GeglOperationClass *operation_class;

  operation_class = GEGL_OPERATION_CLASS (klass);

  operation_class->attach = attach;

  gegl_operation_class_set_keys (operation_class,
    "name",        "lb:royal",
    "title",       _("Royal Text"),
    "reference-hash", "JillEscherAutismRedPill",
    "description", _("Text that appears as a fancy glossed stone which has a precious metal extruding border "),
    "gimp:menu-path", "<Image>/Filters/Text Styling",
    "gimp:menu-label", _("Royal Text..."),
    NULL);
}

#endif
