#include "Curve.h"
#include "math.h"

// based on the rotation of the curve object I approximate the vertices of a ellipse based on a given count
// x = elipse_width * cos( angle ), y = elipse_height * sin( angle )
void ComputeCurve( int count, cpVect *verts, float width, float height, CurveRot rot ){
    float step = M_PI_2 / count;
    switch( rot ){
        case CurveRotNE:
            for( int i = 0; i < count; i++ ){
                float angle = 0 + i * step;
                verts[i] = cpv( width * cos( angle ), height * sin( angle ) );
            }
            break;
        case CurveRotNW:
            for( int i = 0; i < count; i++ ){
                float angle = M_PI_2 + i * step;
                verts[i] = cpv( width * cos( angle ), height * sin( angle ) );
            }
            break;
        case CurveRotSE:
            for( int i = 0; i < count; i++ ){
                float angle = 3 * M_PI_2 + i * step;
                verts[i] = cpv( width * cos( angle ), height * sin( angle ) );
            }
            break;
        case CurveRotSW:
            for( int i = 0; i < count; i++ ){
                float angle = M_PI + i * step;
                verts[i] = cpv( width * cos( angle ), height * sin( angle ) );
            }
            break;
        default:
            break;
    }
}

// chooses the centroid for a curve based on the rotation
static void ChooseGravity( Curve *curve, float width, float height ){
    CurveRot rot = curve->rot;
    switch( rot ){
        case CurveRotNE:
            cpBodySetCenterOfGravity( curve->body, cpv( -width/ 2.0, -height / 2.0) );
            break;
        case CurveRotNW:
            cpBodySetCenterOfGravity( curve->body, cpv( width/ 2.0, -height / 2.0) );
            break;
        case CurveRotSE:
            cpBodySetCenterOfGravity( curve->body, cpv( -width/ 2.0, +height / 2.0) );
            break;
        case CurveRotSW:
            cpBodySetCenterOfGravity( curve->body, cpv( width/ 2.0, +height / 2.0) );
            break;
        default:
            break;
    }
}

Curve* InitCurve(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, CurveRot rot ){
    Curve *curve = (Curve*)malloc( sizeof(Curve) );
    curve->precision = 30;
    curve->rot = rot;
    curve->body = cpBodyNewStatic();

    ChooseGravity( curve, width, height );

    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(curve->body, pos);
    cpBodySetVelocity(curve->body, cpvzero);

    cpFloat radius = 75;
    //cpVect *verts = (cpVect*)malloc( curve->precision * sizeof(cpVect) );
    cpVect verts[curve->precision];
    ComputeCurve( curve->precision, verts, width, height, curve->rot );

    curve->shape = cpSpaceAddShape( space, cpPolyShapeNewRaw( curve->body, curve->precision, verts, radius ));

    curve->rect.x = cpBodyGetPosition(curve->body).x; 
    curve->rect.y = - cpBodyGetPosition(curve->body).y; 
    curve->rect.w = width;
    curve->rect.h = height;
    return curve;
}

// prints vertices of curve polygon to the sdl window
void ShowCurvature(SDL_Renderer *renderer, Curve *curve){
    SDL_SetRenderDrawColor( renderer, 150,200, 150, 255);
    cpVect vert;
    SDL_Rect r;
    cpVect pos = cpBodyGetPosition( curve->body );
    for( int i = 0; i < curve->precision; i++ ){
        vert = cpPolyShapeGetVert( curve->shape, i );
        CurveRot rot = curve->rot;
        switch( rot ){
            case CurveRotNE:
                r.x = pos.x - curve->rect.w / 2.0 + vert.x;
                r.y = -(pos.y + vert.y) + curve->rect.h / 2.0;
                break;
            case CurveRotNW:
                r.x = pos.x + curve->rect.w / 2.0 + vert.x;
                r.y = -(pos.y + vert.y) + curve->rect.h / 2.0;
                break;
            case CurveRotSE:
                r.x = pos.x - curve->rect.w / 2.0 + vert.x;
                r.y = -(pos.y + vert.y) - curve->rect.h / 2.0;
                break;
            case CurveRotSW:
                r.x = pos.x + curve->rect.w / 2.0 + vert.x;
                r.y = -(pos.y + vert.y) - curve->rect.h / 2.0;
                break;
            default:
                break;
        }
        r.w = 5;
        r.h = 5;
        SDL_RenderDrawRect( renderer, &r );
    }
}
            
// prints out the curve based on its rotation
void PrintCurve( SDL_Renderer *renderer, Curve *curve, SDL_Texture *texture ){
    cpVect pos = cpBodyGetPosition(curve->body);
    curve->rect.x = pos.x - curve->rect.w / 2.0;
    curve->rect.y = -pos.y - curve->rect.h / 2.0;
    switch( curve->rot ){
        case CurveRotNE:
            SDL_RenderCopyEx(renderer, texture , NULL, &curve->rect, 0, NULL, SDL_FLIP_VERTICAL);
            ShowCurvature( renderer, curve );
            break;
        case CurveRotNW:
            SDL_RenderCopyEx(renderer, texture , NULL, &curve->rect, 180, NULL, SDL_FLIP_NONE);
            ShowCurvature( renderer, curve );
            break;
        case CurveRotSE:
            SDL_RenderCopyEx(renderer, texture , NULL, &curve->rect, 0, NULL, SDL_FLIP_NONE);
            ShowCurvature( renderer, curve );
            break;
        case CurveRotSW:
            SDL_RenderCopyEx(renderer, texture , NULL, &curve->rect, 0, NULL, SDL_FLIP_HORIZONTAL);
            ShowCurvature( renderer, curve );
            break;
        default:
            break;
    }
}

void DeleteCurve( cpSpace *space, Curve *curve ){
    cpSpaceRemoveBody( space, curve->body );
    cpSpaceRemoveShape( space, curve->shape );
    cpShapeFree(curve->shape);
    cpBodyFree(curve->body);
    free(curve);
}
