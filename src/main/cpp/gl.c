//
// Created by Swung0x48 on 2024/10/8.
//

#include "includes.h"
#include <GL/gl.h>

/*
 * Miscellaneous
 */

GLAPI void GLAPIENTRY glClearIndex( GLfloat c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glClearColor( GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glClear( GLbitfield mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glIndexMask( GLuint mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glColorMask( GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glAlphaFunc( GLenum func, GLclampf ref ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glBlendFunc( GLenum sfactor, GLenum dfactor ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLogicOp( GLenum opcode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glCullFace( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFrontFace( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPointSize( GLfloat size ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLineWidth( GLfloat width ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLineStipple( GLint factor, GLushort pattern ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPolygonMode( GLenum face, GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPolygonOffset( GLfloat factor, GLfloat units ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPolygonStipple( const GLubyte *mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetPolygonStipple( GLubyte *mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEdgeFlag( GLboolean flag ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEdgeFlagv( const GLboolean *flag ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glScissor( GLint x, GLint y, GLsizei width, GLsizei height) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glClipPlane( GLenum plane, const GLdouble *equation ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetClipPlane( GLenum plane, GLdouble *equation ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDrawBuffer( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glReadBuffer( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEnable( GLenum cap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDisable( GLenum cap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI GLboolean GLAPIENTRY glIsEnabled( GLenum cap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return GL_FALSE; }


GLAPI void GLAPIENTRY glEnableClientState( GLenum cap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */

GLAPI void GLAPIENTRY glDisableClientState( GLenum cap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */


GLAPI void GLAPIENTRY glGetBooleanv( GLenum pname, GLboolean *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetDoublev( GLenum pname, GLdouble *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetFloatv( GLenum pname, GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetIntegerv( GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glPushAttrib( GLbitfield mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPopAttrib( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glPushClientAttrib( GLbitfield mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */

GLAPI void GLAPIENTRY glPopClientAttrib( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */


GLAPI GLint GLAPIENTRY glRenderMode( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return 0; }

//GLAPI GLenum GLAPIENTRY glGetError( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
//                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

//GLAPI const GLubyte * GLAPIENTRY glGetString( GLenum name ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
//                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFinish( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFlush( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glHint( GLenum target, GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Depth Buffer
 */

GLAPI void GLAPIENTRY glClearDepth( GLclampd depth ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(%.2lf)", RENDERERNAME, __FUNCTION__, depth); }

GLAPI void GLAPIENTRY glDepthFunc( GLenum func ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDepthMask( GLboolean flag ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDepthRange( GLclampd near_val, GLclampd far_val ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Accumulation Buffer
 */

GLAPI void GLAPIENTRY glClearAccum( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glAccum( GLenum op, GLfloat value ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Transformation
 */

GLAPI void GLAPIENTRY glMatrixMode( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glOrtho( GLdouble left, GLdouble right,
                               GLdouble bottom, GLdouble top,
                               GLdouble near_val, GLdouble far_val ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFrustum( GLdouble left, GLdouble right,
                                 GLdouble bottom, GLdouble top,
                                 GLdouble near_val, GLdouble far_val ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glViewport( GLint x, GLint y,
                                  GLsizei width, GLsizei height ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPushMatrix( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPopMatrix( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLoadIdentity( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLoadMatrixd( const GLdouble *m ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLoadMatrixf( const GLfloat *m ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glMultMatrixd( const GLdouble *m ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMultMatrixf( const GLfloat *m ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRotated( GLdouble angle,
                                 GLdouble x, GLdouble y, GLdouble z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRotatef( GLfloat angle,
                                 GLfloat x, GLfloat y, GLfloat z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glScaled( GLdouble x, GLdouble y, GLdouble z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glScalef( GLfloat x, GLfloat y, GLfloat z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTranslated( GLdouble x, GLdouble y, GLdouble z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTranslatef( GLfloat x, GLfloat y, GLfloat z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Display Lists
 */

GLAPI GLboolean GLAPIENTRY glIsList( GLuint list ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return GL_FALSE; }

GLAPI void GLAPIENTRY glDeleteLists( GLuint list, GLsizei range ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI GLuint GLAPIENTRY glGenLists( GLsizei range ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return 0; }

GLAPI void GLAPIENTRY glNewList( GLuint list, GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEndList( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glCallList( GLuint list ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glCallLists( GLsizei n, GLenum type,
                                   const GLvoid *lists ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glListBase( GLuint base ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Drawing Functions
 */

GLAPI void GLAPIENTRY glBegin( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEnd( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glVertex2d( GLdouble x, GLdouble y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2f( GLfloat x, GLfloat y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2i( GLint x, GLint y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2s( GLshort x, GLshort y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glVertex3d( GLdouble x, GLdouble y, GLdouble z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3f( GLfloat x, GLfloat y, GLfloat z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3i( GLint x, GLint y, GLint z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3s( GLshort x, GLshort y, GLshort z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glVertex4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4i( GLint x, GLint y, GLint z, GLint w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4s( GLshort x, GLshort y, GLshort z, GLshort w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glVertex2dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex2sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glVertex3dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex3sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glVertex4dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glVertex4sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glNormal3b( GLbyte nx, GLbyte ny, GLbyte nz ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3d( GLdouble nx, GLdouble ny, GLdouble nz ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3f( GLfloat nx, GLfloat ny, GLfloat nz ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3i( GLint nx, GLint ny, GLint nz ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3s( GLshort nx, GLshort ny, GLshort nz ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glNormal3bv( const GLbyte *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glNormal3sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glIndexd( GLdouble c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexf( GLfloat c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexi( GLint c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexs( GLshort c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexub( GLubyte c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */

GLAPI void GLAPIENTRY glIndexdv( const GLdouble *c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexfv( const GLfloat *c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexiv( const GLint *c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexsv( const GLshort *c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glIndexubv( const GLubyte *c ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }  /* 1.1 */

GLAPI void GLAPIENTRY glColor3b( GLbyte red, GLbyte green, GLbyte blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3d( GLdouble red, GLdouble green, GLdouble blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3f( GLfloat red, GLfloat green, GLfloat blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3i( GLint red, GLint green, GLint blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3s( GLshort red, GLshort green, GLshort blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3ub( GLubyte red, GLubyte green, GLubyte blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3ui( GLuint red, GLuint green, GLuint blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3us( GLushort red, GLushort green, GLushort blue ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glColor4b( GLbyte red, GLbyte green,
                                 GLbyte blue, GLbyte alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4d( GLdouble red, GLdouble green,
                                 GLdouble blue, GLdouble alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4f( GLfloat red, GLfloat green,
                                 GLfloat blue, GLfloat alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4i( GLint red, GLint green,
                                 GLint blue, GLint alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4s( GLshort red, GLshort green,
                                 GLshort blue, GLshort alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4ub( GLubyte red, GLubyte green,
                                  GLubyte blue, GLubyte alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4ui( GLuint red, GLuint green,
                                  GLuint blue, GLuint alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4us( GLushort red, GLushort green,
                                  GLushort blue, GLushort alpha ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glColor3bv( const GLbyte *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3ubv( const GLubyte *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3uiv( const GLuint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor3usv( const GLushort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glColor4bv( const GLbyte *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4ubv( const GLubyte *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4uiv( const GLuint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glColor4usv( const GLushort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glTexCoord1d( GLdouble s ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1f( GLfloat s ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1i( GLint s ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1s( GLshort s ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord2d( GLdouble s, GLdouble t ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2f( GLfloat s, GLfloat t ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2i( GLint s, GLint t ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2s( GLshort s, GLshort t ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord3d( GLdouble s, GLdouble t, GLdouble r ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3f( GLfloat s, GLfloat t, GLfloat r ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3i( GLint s, GLint t, GLint r ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3s( GLshort s, GLshort t, GLshort r ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord4d( GLdouble s, GLdouble t, GLdouble r, GLdouble q ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4f( GLfloat s, GLfloat t, GLfloat r, GLfloat q ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4i( GLint s, GLint t, GLint r, GLint q ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4s( GLshort s, GLshort t, GLshort r, GLshort q ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord1dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord1sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord2dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord2sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord3dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord3sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoord4dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexCoord4sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glRasterPos2d( GLdouble x, GLdouble y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2f( GLfloat x, GLfloat y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2i( GLint x, GLint y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2s( GLshort x, GLshort y ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRasterPos3d( GLdouble x, GLdouble y, GLdouble z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3f( GLfloat x, GLfloat y, GLfloat z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3i( GLint x, GLint y, GLint z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3s( GLshort x, GLshort y, GLshort z ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRasterPos4d( GLdouble x, GLdouble y, GLdouble z, GLdouble w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4f( GLfloat x, GLfloat y, GLfloat z, GLfloat w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4i( GLint x, GLint y, GLint z, GLint w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4s( GLshort x, GLshort y, GLshort z, GLshort w ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRasterPos2dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos2sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRasterPos3dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos3sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glRasterPos4dv( const GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4fv( const GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4iv( const GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRasterPos4sv( const GLshort *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glRectd( GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRectf( GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRecti( GLint x1, GLint y1, GLint x2, GLint y2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRects( GLshort x1, GLshort y1, GLshort x2, GLshort y2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glRectdv( const GLdouble *v1, const GLdouble *v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRectfv( const GLfloat *v1, const GLfloat *v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRectiv( const GLint *v1, const GLint *v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glRectsv( const GLshort *v1, const GLshort *v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Vertex Arrays  (1.1)
 */

GLAPI void GLAPIENTRY glVertexPointer( GLint size, GLenum type,
                                       GLsizei stride, const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glNormalPointer( GLenum type, GLsizei stride,
                                       const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glColorPointer( GLint size, GLenum type,
                                      GLsizei stride, const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glIndexPointer( GLenum type, GLsizei stride,
                                      const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexCoordPointer( GLint size, GLenum type,
                                         GLsizei stride, const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEdgeFlagPointer( GLsizei stride, const GLvoid *ptr ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetPointerv( GLenum pname, GLvoid **params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glArrayElement( GLint i ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDrawArrays( GLenum mode, GLint first, GLsizei count ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDrawElements( GLenum mode, GLsizei count,
                                      GLenum type, const GLvoid *indices ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glInterleavedArrays( GLenum format, GLsizei stride,
                                           const GLvoid *pointer ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

/*
 * Lighting
 */

GLAPI void GLAPIENTRY glShadeModel( GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLightf( GLenum light, GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLighti( GLenum light, GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLightfv( GLenum light, GLenum pname,
                                 const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLightiv( GLenum light, GLenum pname,
                                 const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetLightfv( GLenum light, GLenum pname,
                                    GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetLightiv( GLenum light, GLenum pname,
                                    GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLightModelf( GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLightModeli( GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLightModelfv( GLenum pname, const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glLightModeliv( GLenum pname, const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glMaterialf( GLenum face, GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMateriali( GLenum face, GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMaterialfv( GLenum face, GLenum pname, const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMaterialiv( GLenum face, GLenum pname, const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetMaterialfv( GLenum face, GLenum pname, GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetMaterialiv( GLenum face, GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glColorMaterial( GLenum face, GLenum mode ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Raster functions
 */

GLAPI void GLAPIENTRY glPixelZoom( GLfloat xfactor, GLfloat yfactor ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPixelStoref( GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glPixelStorei( GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPixelTransferf( GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glPixelTransferi( GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPixelMapfv( GLenum map, GLsizei mapsize,
                                    const GLfloat *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glPixelMapuiv( GLenum map, GLsizei mapsize,
                                     const GLuint *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glPixelMapusv( GLenum map, GLsizei mapsize,
                                     const GLushort *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetPixelMapfv( GLenum map, GLfloat *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetPixelMapuiv( GLenum map, GLuint *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetPixelMapusv( GLenum map, GLushort *values ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glBitmap( GLsizei width, GLsizei height,
                                GLfloat xorig, GLfloat yorig,
                                GLfloat xmove, GLfloat ymove,
                                const GLubyte *bitmap ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glReadPixels( GLint x, GLint y,
                                    GLsizei width, GLsizei height,
                                    GLenum format, GLenum type,
                                    GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDrawPixels( GLsizei width, GLsizei height,
                                    GLenum format, GLenum type,
                                    const GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glCopyPixels( GLint x, GLint y,
                                    GLsizei width, GLsizei height,
                                    GLenum type ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

/*
 * Stenciling
 */

GLAPI void GLAPIENTRY glStencilFunc( GLenum func, GLint ref, GLuint mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glStencilMask( GLuint mask ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glStencilOp( GLenum fail, GLenum zfail, GLenum zpass ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glClearStencil( GLint s ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }



/*
 * Texture mapping
 */

GLAPI void GLAPIENTRY glTexGend( GLenum coord, GLenum pname, GLdouble param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexGenf( GLenum coord, GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexGeni( GLenum coord, GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexGendv( GLenum coord, GLenum pname, const GLdouble *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexGenfv( GLenum coord, GLenum pname, const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexGeniv( GLenum coord, GLenum pname, const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetTexGendv( GLenum coord, GLenum pname, GLdouble *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetTexGenfv( GLenum coord, GLenum pname, GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetTexGeniv( GLenum coord, GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glTexEnvf( GLenum target, GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexEnvi( GLenum target, GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexEnvfv( GLenum target, GLenum pname, const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexEnviv( GLenum target, GLenum pname, const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetTexEnvfv( GLenum target, GLenum pname, GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetTexEnviv( GLenum target, GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glTexParameterf( GLenum target, GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexParameteri( GLenum target, GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexParameterfv( GLenum target, GLenum pname,
                                        const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glTexParameteriv( GLenum target, GLenum pname,
                                        const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetTexParameterfv( GLenum target,
                                           GLenum pname, GLfloat *params) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetTexParameteriv( GLenum target,
                                           GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetTexLevelParameterfv( GLenum target, GLint level,
                                                GLenum pname, GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetTexLevelParameteriv( GLenum target, GLint level,
                                                GLenum pname, GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glTexImage1D( GLenum target, GLint level,
                                    GLint internalFormat,
                                    GLsizei width, GLint border,
                                    GLenum format, GLenum type,
                                    const GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glTexImage2D( GLenum target, GLint level,
                                    GLint internalFormat,
                                    GLsizei width, GLsizei height,
                                    GLint border, GLenum format, GLenum type,
                                    const GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetTexImage( GLenum target, GLint level,
                                     GLenum format, GLenum type,
                                     GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/* 1.1 functions */

GLAPI void GLAPIENTRY glGenTextures( GLsizei n, GLuint *textures ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glDeleteTextures( GLsizei n, const GLuint *textures) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glBindTexture( GLenum target, GLuint texture ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPrioritizeTextures( GLsizei n,
                                            const GLuint *textures,
                                            const GLclampf *priorities ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI GLboolean GLAPIENTRY glAreTexturesResident( GLsizei n,
                                                  const GLuint *textures,
                                                  GLboolean *residences ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return GL_FALSE; }

GLAPI GLboolean GLAPIENTRY glIsTexture( GLuint texture ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); return GL_FALSE; }


GLAPI void GLAPIENTRY glTexSubImage1D( GLenum target, GLint level,
                                       GLint xoffset,
                                       GLsizei width, GLenum format,
                                       GLenum type, const GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glTexSubImage2D( GLenum target, GLint level,
                                       GLint xoffset, GLint yoffset,
                                       GLsizei width, GLsizei height,
                                       GLenum format, GLenum type,
                                       const GLvoid *pixels ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glCopyTexImage1D( GLenum target, GLint level,
                                        GLenum internalformat,
                                        GLint x, GLint y,
                                        GLsizei width, GLint border ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glCopyTexImage2D( GLenum target, GLint level,
                                        GLenum internalformat,
                                        GLint x, GLint y,
                                        GLsizei width, GLsizei height,
                                        GLint border ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glCopyTexSubImage1D( GLenum target, GLint level,
                                           GLint xoffset, GLint x, GLint y,
                                           GLsizei width ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


GLAPI void GLAPIENTRY glCopyTexSubImage2D( GLenum target, GLint level,
                                           GLint xoffset, GLint yoffset,
                                           GLint x, GLint y,
                                           GLsizei width, GLsizei height ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Evaluators
 */

GLAPI void GLAPIENTRY glMap1d( GLenum target, GLdouble u1, GLdouble u2,
                               GLint stride,
                               GLint order, const GLdouble *points ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMap1f( GLenum target, GLfloat u1, GLfloat u2,
                               GLint stride,
                               GLint order, const GLfloat *points ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glMap2d( GLenum target,
                               GLdouble u1, GLdouble u2, GLint ustride, GLint uorder,
                               GLdouble v1, GLdouble v2, GLint vstride, GLint vorder,
                               const GLdouble *points ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMap2f( GLenum target,
                               GLfloat u1, GLfloat u2, GLint ustride, GLint uorder,
                               GLfloat v1, GLfloat v2, GLint vstride, GLint vorder,
                               const GLfloat *points ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glGetMapdv( GLenum target, GLenum query, GLdouble *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetMapfv( GLenum target, GLenum query, GLfloat *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glGetMapiv( GLenum target, GLenum query, GLint *v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalCoord1d( GLdouble u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glEvalCoord1f( GLfloat u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalCoord1dv( const GLdouble *u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glEvalCoord1fv( const GLfloat *u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalCoord2d( GLdouble u, GLdouble v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glEvalCoord2f( GLfloat u, GLfloat v ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalCoord2dv( const GLdouble *u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glEvalCoord2fv( const GLfloat *u ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glMapGrid1d( GLint un, GLdouble u1, GLdouble u2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMapGrid1f( GLint un, GLfloat u1, GLfloat u2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glMapGrid2d( GLint un, GLdouble u1, GLdouble u2,
                                   GLint vn, GLdouble v1, GLdouble v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }
GLAPI void GLAPIENTRY glMapGrid2f( GLint un, GLfloat u1, GLfloat u2,
                                   GLint vn, GLfloat v1, GLfloat v2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalPoint1( GLint i ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalPoint2( GLint i, GLint j ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalMesh1( GLenum mode, GLint i1, GLint i2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glEvalMesh2( GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2 ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Fog
 */

GLAPI void GLAPIENTRY glFogf( GLenum pname, GLfloat param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFogi( GLenum pname, GLint param ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFogfv( GLenum pname, const GLfloat *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glFogiv( GLenum pname, const GLint *params ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }


/*
 * Selection and Feedback
 */

GLAPI void GLAPIENTRY glFeedbackBuffer( GLsizei size, GLenum type, GLfloat *buffer ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPassThrough( GLfloat token ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glSelectBuffer( GLsizei size, GLuint *buffer ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glInitNames( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glLoadName( GLuint name ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPushName( GLuint name ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }

GLAPI void GLAPIENTRY glPopName( void ) { __android_log_print(ANDROID_LOG_VERBOSE, RENDERERNAME,
                        "Unimplemented function: %s @ %s(...)", RENDERERNAME, __FUNCTION__); }