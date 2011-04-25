/** \file 
 \brief Камеры для наблюдения, отладки и т.д.
 Выдраны из DXUT с небольшими исправлениями и удалением ненужного.


 \todo поправить код-стиль
 \todo убрать FLOAT на float
  \todo Удалить лишние геймпадовые типы.
  \todo Избавиться от зависимости от d3dx-математики.



*/

#ifdef WIN32 // только для windows


#pragma once

#include <stdexcept>
#include <windows.h>

#ifdef GB_D3DX9
  #include <d3dx9.h>
  #include <d3dx9Math.h>
#endif

#ifndef GB_D3DX9
  #error Пока требуется математика из D3DX. Макрос GB_D3DX9 должен быть определён
#endif


#include <XInput.h>
#include <zmouse.h>


namespace gb {

namespace devhelp {


//////////////////////////////////////////////////////////////////////////
//							 H
//////////////////////////////////////////////////////////////////////////

#define KEY_WAS_DOWN_MASK 0x80
#define KEY_IS_DOWN_MASK  0x01

#define MOUSE_LEFT_BUTTON   0x01
#define MOUSE_MIDDLE_BUTTON 0x02
#define MOUSE_RIGHT_BUTTON  0x04
#define MOUSE_WHEEL         0x08



enum D3DUtil_CameraKeys
{
    CAM_STRAFE_LEFT = 0,
    CAM_STRAFE_RIGHT,
    CAM_MOVE_FORWARD,
    CAM_MOVE_BACKWARD,
    CAM_MOVE_UP,
    CAM_MOVE_DOWN,
    CAM_RESET,
    CAM_CONTROLDOWN,
    CAM_MAX_KEYS,
    CAM_UNKNOWN = 0xFF
};

#define MYUT_MAX_CONTROLLERS 4  // XInput handles up to 4 controllers 

				 
struct MYUT_GAMEPAD
{
    // From XINPUT_GAMEPAD
    WORD    wButtons;
    BYTE    bLeftTrigger;
    BYTE    bRightTrigger;
    SHORT   sThumbLX;
    SHORT   sThumbLY;
    SHORT   sThumbRX;
    SHORT   sThumbRY;

    // Device properties
    XINPUT_CAPABILITIES caps;
    bool    bConnected; // If the controller is currently connected
    bool    bInserted;  // If the controller was inserted this frame
    bool    bRemoved;   // If the controller was removed this frame

    // Thumb stick values converted to range [-1,+1]
    float   fThumbRX;
    float   fThumbRY;
    float   fThumbLX;
    float   fThumbLY;

    // Records which buttons were pressed this frame.
    // These are only set on the first frame that the button is pressed
    WORD    wPressedButtons;
    bool    bPressedLeftTrigger;
    bool    bPressedRightTrigger;

    // Last state of the buttons
    WORD    wLastButtons;
    bool    bLastLeftTrigger;
    bool    bLastRightTrigger;
};

 

class ArcBall  {
public:
    ArcBall();

    // Functions to change behavior
    void reset(); 
    void setTranslationRadius( FLOAT fRadiusTranslation ) { m_fRadiusTranslation = fRadiusTranslation; }
    void setWindow( INT nWidth, INT nHeight, FLOAT fRadius = 0.9f ) { m_nWidth = nWidth; m_nHeight = nHeight; m_fRadius = fRadius; m_vCenter = D3DXVECTOR2(m_nWidth/2.0f,m_nHeight/2.0f); }
    void setOffset( INT nX, INT nY ) { m_Offset.x = nX; m_Offset.y = nY; }

    //! \brief  Call these from client and use GetRotationMatrix() to read new rotation matrix
    void onBegin( int nX, int nY );  // start the rotation (pass current mouse position)
    void onMove( int nX, int nY );   // continue the rotation (pass current mouse position)
    void onEnd();                    // end the rotation 

    //! \brief  Or call this to automatically handle left, middle, right buttons
    LRESULT     handleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    // Functions to get/set state
    const D3DXMATRIX* getRotationMatrix()                   { return D3DXMatrixRotationQuaternion(&m_mRotation, &m_qNow); };
    const D3DXMATRIX* getTranslationMatrix() const          { return &m_mTranslation; }
    const D3DXMATRIX* getTranslationDeltaMatrix() const     { return &m_mTranslationDelta; }

    bool        isBeingDragged() const                      { return m_bDrag; }
    D3DXQUATERNION getQuatNow() const                       { return m_qNow; }
    void        setQuatNow( D3DXQUATERNION q ) { m_qNow = q; }

    static D3DXQUATERNION quatFromBallPoints( const D3DXVECTOR3 &vFrom, const D3DXVECTOR3 &vTo );


protected:
    D3DXMATRIXA16  m_mRotation;         ///< Matrix for arc ball's orientation
    D3DXMATRIXA16  m_mTranslation;      ///< Matrix for arc ball's position
    D3DXMATRIXA16  m_mTranslationDelta; ///< Matrix for arc ball's position

    POINT          m_Offset;   ///< window offset, or upper-left corner of window
    INT            m_nWidth;   ///< arc ball's window width
    INT            m_nHeight;  ///< arc ball's window height
    D3DXVECTOR2    m_vCenter;  ///< center of arc ball 
    FLOAT          m_fRadius;  ///< arc ball's radius in screen coords
    FLOAT          m_fRadiusTranslation; ///< arc ball's radius for translating the target

    D3DXQUATERNION m_qDown;             ///< Quaternion before button down
    D3DXQUATERNION m_qNow;              ///< Composite quaternion for current drag
    bool           m_bDrag;             ///< Whether user is dragging arc ball

    POINT          m_ptLastMouse;      ///< position of last mouse point
    D3DXVECTOR3    m_vDownPt;           ///< starting point of rotation arc
    D3DXVECTOR3    m_vCurrentPt;        ///< current point of rotation arc

    D3DXVECTOR3    screenToVector( float fScreenPtX, float fScreenPtY );
};



class BaseCamera {
public:
    BaseCamera();

	//! \brief Сделать камеру текущей
	virtual HRESULT makeCurrent(IDirect3DDevice9* pDevice) = 0; 

    // Call these from client and use Get*Matrix() to read new matrices
    virtual LRESULT handleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual void    frameMove( FLOAT fElapsedTime ) = 0;

    // Functions to change camera matrices

    virtual void reset(); 
    virtual void setViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
    virtual void setProjParams( FLOAT fFOV, FLOAT fAspect, FLOAT fNearPlane, FLOAT fFarPlane );

    // Functions to change behavior

    virtual void setDragRect( RECT &rc ) { m_rcDrag = rc; }
    void setInvertPitch( bool bInvertPitch ) { m_bInvertPitch = bInvertPitch; }
    void setDrag( bool bMovementDrag, FLOAT fTotalDragTimeToZero = 0.25f ) { m_bMovementDrag = bMovementDrag; m_fTotalDragTimeToZero = fTotalDragTimeToZero; }
    void setEnableYAxisMovement( bool bEnableYAxisMovement ) { m_bEnableYAxisMovement = bEnableYAxisMovement; }
    void setEnablePositionMovement( bool bEnablePositionMovement ) { m_bEnablePositionMovement = bEnablePositionMovement; }
    void setClipToBoundary( bool bClipToBoundary, D3DXVECTOR3* pvMinBoundary, D3DXVECTOR3* pvMaxBoundary ) { m_bClipToBoundary = bClipToBoundary; if( pvMinBoundary ) m_vMinBoundary = *pvMinBoundary; if( pvMaxBoundary ) m_vMaxBoundary = *pvMaxBoundary; }
    void setScalers( FLOAT fRotationScaler = 0.01f, FLOAT fMoveScaler = 5.0f )  { m_fRotationScaler = fRotationScaler; m_fMoveScaler = fMoveScaler; }
    void setNumberOfFramesToSmoothMouseData( int nFrames ) { if( nFrames > 0 ) m_fFramesToSmoothMouseData = (float)nFrames; }

    // Functions to get state
    const D3DXMATRIX*  getViewMatrix() const { return &m_mView; }
    const D3DXMATRIX*  getProjMatrix() const { return &m_mProj; }
    const D3DXVECTOR3* getEyePoint() const      { return &m_vEye; }
    const D3DXVECTOR3* getLookAtPoint() const   { return &m_vLookAt; }
    float getNearClipPlane() const { return m_fNearPlane; }
    float getFarClipPlane() const { return m_fFarPlane; }

    bool isBeingDragged() const         { return (m_bMouseLButtonDown || m_bMouseMButtonDown || m_bMouseRButtonDown); }
    bool isMouseLButtonDown() const     { return m_bMouseLButtonDown; } 
    bool isMouseMButtonDown() const     { return m_bMouseMButtonDown; } 
    bool isMouseRButtonDown() const     { return m_bMouseRButtonDown; } 



protected:
    // Functions to map a WM_KEYDOWN key to a D3DUtil_CameraKeys enum
    // >>>>  old  : virtual 
		static D3DUtil_CameraKeys mapKey( UINT nKey );  

    bool isKeyDown( BYTE key ) const { return( (key & KEY_IS_DOWN_MASK) == KEY_IS_DOWN_MASK ); }
    bool wasKeyDown( BYTE key ) const { return( (key & KEY_WAS_DOWN_MASK) == KEY_WAS_DOWN_MASK ); }

    void constrainToBoundary( D3DXVECTOR3* pV );
    void updateVelocity( float fElapsedTime );
    void getInput( bool bGetKeyboardInput, bool bGetMouseInput, bool bGetGamepadInput, bool bResetCursorAfterMove );

	/*
	void MYUTGetMonitorInfo( UnknownType param1, MONITORINFO* mi ) 
	{
		throw std::exception("The method or operation is not implemented.");
	}
	*/


    D3DXMATRIX            m_mView;              ///< View matrix 
    D3DXMATRIX            m_mProj;              ///< Projection matrix

    MYUT_GAMEPAD          m_GamePad[MYUT_MAX_CONTROLLERS]; ///< XInput controller state
    D3DXVECTOR3           m_vGamePadLeftThumb;
    D3DXVECTOR3           m_vGamePadRightThumb;
    double                m_GamePadLastActive[MYUT_MAX_CONTROLLERS];

    int                   m_cKeysDown;            ///< Number of camera keys that are down.
    BYTE                  m_aKeys[CAM_MAX_KEYS];  ///< State of input - KEY_WAS_DOWN_MASK|KEY_IS_DOWN_MASK
    D3DXVECTOR3           m_vKeyboardDirection;   ///< Direction vector of keyboard input
    POINT                 m_ptLastMousePosition;  ///< Last absolute position of mouse cursor
    bool                  m_bMouseLButtonDown;    ///< True if left button is down 
    bool                  m_bMouseMButtonDown;    ///< True if middle button is down 
    bool                  m_bMouseRButtonDown;    ///< True if right button is down 
    int                   m_nCurrentButtonMask;   ///< mask of which buttons are down
    int                   m_nMouseWheelDelta;     ///< Amount of middle wheel scroll (+/-) 
    D3DXVECTOR2           m_vMouseDelta;          ///< Mouse relative delta smoothed over a few frames
    float                 m_fFramesToSmoothMouseData; ///< Number of frames to smooth mouse data over

    D3DXVECTOR3           m_vDefaultEye;          ///< Default camera eye position
    D3DXVECTOR3           m_vDefaultLookAt;       ///< Default LookAt position
    D3DXVECTOR3           m_vEye;                 ///< Camera eye position
    D3DXVECTOR3           m_vLookAt;              ///< LookAt position
    float                 m_fCameraYawAngle;      ///< Yaw angle of camera
    float                 m_fCameraPitchAngle;    ///< Pitch angle of camera

    RECT                  m_rcDrag;               ///< Rectangle within which a drag can be initiated.
    D3DXVECTOR3           m_vVelocity;            ///< Velocity of camera
    bool                  m_bMovementDrag;        ///< If true, then camera movement will slow to a stop otherwise movement is instant
    D3DXVECTOR3           m_vVelocityDrag;        ///< Velocity drag force
    FLOAT                 m_fDragTimer;           ///< Countdown timer to apply drag
    FLOAT                 m_fTotalDragTimeToZero; ///< Time it takes for velocity to go from full to 0
    D3DXVECTOR2           m_vRotVelocity;         ///< Velocity of camera

    float                 m_fFOV;                 ///< Field of view
    float                 m_fAspect;              ///< Aspect ratio
    float                 m_fNearPlane;           ///< Near plane
    float                 m_fFarPlane;            ///< Far plane

    float                 m_fRotationScaler;      ///< Scaler for rotation
    float                 m_fMoveScaler;          ///< Scaler for movement

    bool                  m_bInvertPitch;         ///< Invert the pitch axis
    bool                  m_bEnablePositionMovement; ///< If true, then the user can translate the camera/model 
    bool                  m_bEnableYAxisMovement; ///< If true, then camera can move in the y-axis

    bool                  m_bClipToBoundary;      ///< If true, then the camera will be clipped to the boundary
    D3DXVECTOR3           m_vMinBoundary;         ///< Min point in clip boundary
    D3DXVECTOR3           m_vMaxBoundary;         ///< Max point in clip boundary
};
// end class


/** \brief  Simple first person camera class that moves and rotates.
        It allows yaw and pitch but not roll.  It uses WM_KEYDOWN and 
        GetCursorPos() to respond to keyboard and mouse input and updates the 
       view matrix based on input.  */
class FirstPersonCamera : public BaseCamera {
public:
    FirstPersonCamera();

	//! \brief Сделать камеру текущей
	virtual HRESULT makeCurrent(IDirect3DDevice9* pDevice) 
	{
	  HRESULT hr =0;
       // hr |= pDevice->SetTransform( D3DTS_WORLD ,  GetWorldMatrix() );
       hr |= pDevice->SetTransform(D3DTS_VIEW ,  getViewMatrix() );
       hr |= pDevice->SetTransform(D3DTS_PROJECTION ,  getProjMatrix() );

      return hr;
	}; 

    //! \brief Call these from client and use Get*Matrix() to read new matrices
    virtual void frameMove( FLOAT fElapsedTime );

    //  Functions to change behavior
    void setRotateButtons( bool bLeft, bool bMiddle, bool bRight, bool bRotateWithoutButtonDown = false );

    void setResetCursorAfterMove( bool bResetCursorAfterMove ) { m_bResetCursorAfterMove = bResetCursorAfterMove; }

    // Functions to get state
    D3DXMATRIX*  getWorldMatrix()            { return &m_mCameraWorld; }

    const D3DXVECTOR3* getWorldRight() const { return (D3DXVECTOR3*)&m_mCameraWorld._11; } 
    const D3DXVECTOR3* getWorldUp() const    { return (D3DXVECTOR3*)&m_mCameraWorld._21; }
    const D3DXVECTOR3* getWorldAhead() const { return (D3DXVECTOR3*)&m_mCameraWorld._31; }
    const D3DXVECTOR3* getEyePoint() const      { return (D3DXVECTOR3*)&m_mCameraWorld._41; }

protected:
    D3DXMATRIX m_mCameraWorld;       ///< World matrix of the camera (inverse of the view matrix)

    int        m_nActiveButtonMask;  ///< Mask to determine which button to enable for rotation
    bool       m_bRotateWithoutButtonDown;

    bool       m_bResetCursorAfterMove; ///< If true, the class will reset the cursor position so that the cursor always has space to move 
};
// end class



/** \brief  Simple model viewing camera class that rotates around the object. */
class ModelViewerCamera : public BaseCamera
{
public:
    ModelViewerCamera();

	//! \brief Сделать камеру текущей
	virtual HRESULT makeCurrent(IDirect3DDevice9* pDevice) 
	{
	  HRESULT hr =0;
       hr |= pDevice->SetTransform( D3DTS_WORLD ,  getWorldMatrix() );
       hr |= pDevice->SetTransform(D3DTS_VIEW ,  getViewMatrix() );
       hr |= pDevice->SetTransform(D3DTS_PROJECTION ,  getProjMatrix() );

      return hr;
	}; 

    // Call these from client and use Get*Matrix() to read new matrices
    virtual LRESULT handleMessages( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );
    virtual void frameMove( FLOAT fElapsedTime );

   
    // Functions to change behavior
    virtual void setDragRect( RECT &rc );
    void reset(); 
    void setViewParams( D3DXVECTOR3* pvEyePt, D3DXVECTOR3* pvLookatPt );
    void setButtonMasks( int nRotateModelButtonMask = MOUSE_LEFT_BUTTON, int nZoomButtonMask = MOUSE_WHEEL, int nRotateCameraButtonMask = MOUSE_RIGHT_BUTTON ) { m_nRotateModelButtonMask = nRotateModelButtonMask, m_nZoomButtonMask = nZoomButtonMask; m_nRotateCameraButtonMask = nRotateCameraButtonMask; }
    
    void setAttachCameraToModel( bool bEnable = false ) { m_bAttachCameraToModel = bEnable; }
    void setWindow( int nWidth, int nHeight, float fArcballRadius=0.9f ) { m_WorldArcBall.setWindow( nWidth, nHeight, fArcballRadius ); m_ViewArcBall.setWindow( nWidth, nHeight, fArcballRadius ); }
    void setRadius( float fDefaultRadius=5.0f, float fMinRadius=1.0f, float fMaxRadius=FLT_MAX  ) { m_fDefaultRadius = m_fRadius = fDefaultRadius; m_fMinRadius = fMinRadius; m_fMaxRadius = fMaxRadius; m_bDragSinceLastUpdate = true; }
    void setModelCenter( D3DXVECTOR3 vModelCenter ) { m_vModelCenter = vModelCenter; }
    void setLimitPitch( bool bLimitPitch ) { m_bLimitPitch = bLimitPitch; }
    void setViewQuat( D3DXQUATERNION q ) { m_ViewArcBall.setQuatNow( q ); m_bDragSinceLastUpdate = true; }
    void setWorldQuat( D3DXQUATERNION q ) { m_WorldArcBall.setQuatNow( q ); m_bDragSinceLastUpdate = true; }

    // Functions to get state
    const D3DXMATRIX* getWorldMatrix() const { return &m_mWorld; }
    void setWorldMatrix( D3DXMATRIX &mWorld ) { m_mWorld = mWorld; m_bDragSinceLastUpdate = true; }

protected:
    ArcBall  m_WorldArcBall;
    ArcBall  m_ViewArcBall;
    D3DXVECTOR3  m_vModelCenter;
    D3DXMATRIX   m_mModelLastRot;        // Last arcball rotation matrix for model 
    D3DXMATRIX   m_mModelRot;            // Rotation matrix of model
    D3DXMATRIX   m_mWorld;               // World matrix of model

    int          m_nRotateModelButtonMask;
    int          m_nZoomButtonMask;
    int          m_nRotateCameraButtonMask;

    bool         m_bAttachCameraToModel;
    bool         m_bLimitPitch;
    float        m_fRadius;              // Distance from the camera to model 
    float        m_fDefaultRadius;       // Distance from the camera to model 
    float        m_fMinRadius;           // Min radius
    float        m_fMaxRadius;           // Max radius
    bool         m_bDragSinceLastUpdate; // True if mouse drag has happened since last time FrameMove is called.

    D3DXMATRIX   m_mCameraRotLast;

};
// end class




 }
 // end namespace
}
// end namespace

#endif // #ifdef WIN32
// end file


// end  file