//**************************************************************//
//  Effect File exported by RenderMonkey 1.6
//**************************************************************//

//--------------------------------------------------------------//
// billib_rotate
//--------------------------------------------------------------//
// ks777:  CRmFXExporterPlugIn::OutputPass 
//--------------------------------------------------------------//
// pass0
//--------------------------------------------------------------//
// ks777:  CRmFXExporterPlugIn::OutputPassData 
string billib_rotate_pass0_ScreenAlignedQuad : ModelData = "..\\_KSW\\resources\\xmesh\\engine\\quadxy.x";

 
float4x4 mWorldViewProj : ViewProjection ;
float4x4 mView : View  ;

float ang
<
   string UIName = "ang";
   string UIWidget = "Numeric";
   bool UIVisible =  false;
   float UIMin = -1.00;
   float UIMax = 0.00;
> = float( -0.34 );

float4 posit
<
   string UIName = "posit";
   string UIWidget = "Direction";
   bool UIVisible =  false;
   float4 UIMin = float4( -10.00, -10.00, -10.00, -10.00 );
   float4 UIMax = float4( 10.00, 10.00, 10.00, 10.00 );
   bool Normalize =  false;
> = float4( 0.00, 0.00, 0.00, 1.00 );
float size
<
   string UIName = "size";
   string UIWidget = "Numeric";
   bool UIVisible =  true;
   float UIMin = 0.00;
   float UIMax = 0.00;
> = float( 0.80 );

struct VS_OUTPUT 
{
   float4 Pos: POSITION;
   float2 texCoord: TEXCOORD0;
};

VS_OUTPUT vs_main(float4 Pos: POSITION, float2 txc: TEXCOORD0)
{
   VS_OUTPUT Out;

 float sinAn, cosAn;  sincos (ang, sinAn, cosAn);
   float2x2 mrot;
 mrot[0][0] =  cosAn;
 mrot[0][1] = -sinAn;
 mrot[1][0] = sinAn;
 mrot[1][1] = cosAn;
 
 //float4 vPosNew = mul( float2(mrot), inPos );
float2 vPosNew = mul( mrot, Pos );
Pos.x = vPosNew.x;
Pos.y = vPosNew.y; 



   // Grab X and Y eye-space vectors in world-space ...
   float3 dirX = mView[0];
   float3 dirY = mView[1];

   // ... which are used for billboarding
   float3 pos = posit + size * (Pos.x * dirX + Pos.y * dirY);

   Out.Pos = mul(mWorldViewProj, float4(pos, 1));
   
  // Out.texCoord = 0.5 * Pos.xy + 0.5; //Out.texCoord = 0.5 * Pos.xy + 0.5;
  Out.texCoord = txc ;   



   return Out;
}






float4 color
<
   string UIName = "color";
   string UIWidget = "Color";
   bool UIVisible =  true;
> = float4( 1.00, 1.00, 1.00, 1.00 ) ;
 
 texture txtr_Tex
<
   string ResourceName = "..\\_KSW\\resources\\texture\\2d\\engine\\default.bmp";
>;
sampler2D smplr = sampler_state
{
   Texture = (txtr_Tex);
   MAGFILTER = LINEAR;
   MINFILTER = LINEAR;
   MIPFILTER = LINEAR;
   ADDRESSU = WRAP;
   ADDRESSV = WRAP;
};
 
float4 ps_main(float2 texCoord: TEXCOORD0) : COLOR {
   float4 corona = tex2D( smplr, texCoord);
    return   corona * color;
}








//--------------------------------------------------------------//
// Technique Section for billib_rotate
//--------------------------------------------------------------//
// ks777:  CRmFXExporterPlugIn::OutputTechniqueEffect 
technique billib_rotate
{
// ks777:  CRmFXExporterPlugIn::OutputTechniquePass 
   pass pass0
// ks777:  CRmFXExporterPlugIn::OutputTechniquePassScript 
   {
      ZENABLE = FALSE;
      SRCBLEND = ONE;
      DESTBLEND = ONE;
      CULLMODE = NONE;
      ALPHABLENDENABLE = TRUE;

      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }

}

