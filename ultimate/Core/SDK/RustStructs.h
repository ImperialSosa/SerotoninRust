#pragma once

namespace RustStructs
{
	enum BUTTON // TypeDefIndex: 1982
	{
		// Fields
		FORWARD = 2,
		BACKWARD = 4,
		LEFT = 8,
		RIGHT = 16,
		JUMP = 32,
		DUCK = 64,
		SPRINT = 128,
		USE = 256,
		FIRE_PRIMARY = 1024,
		FIRE_SECONDARY = 2048,
		RELOAD = 8192,
		FIRE_THIRD = 134217728,
	};

	enum class Signal {
		Attack,
		Alt_Attack,
		DryFire,
		Reload,
		Deploy,
		Flinch_Head,
		Flinch_Chest,
		Flinch_Stomach,
		Flinch_RearHead,
		Flinch_RearTorso,
		Throw,
		Relax,
		Gesture,
		PhysImpact,
		Eat,
		Startled
	};

	enum class ModelState_Flag
	{
		Ducked = 1,
		Jumped = 2,
		OnGround = 4,
		Sleeping = 8,
		Sprinting = 16,
		OnLadder = 32,
		Flying = 64,
		Aiming = 128,
		Prone = 256,
		Mounted = 512,
		Relaxed = 1024,
		Crawling = 4096,
		HasParachute = 32768,
	};

	enum KeyCode // TypeDefIndex: 10181
	{
		// Fields
		Nonez = 0,
		Backspace = 8,
		Delete = 127,
		Tab = 9,
		Clear = 12,
		Return = 13,
		Pause = 19,
		Escape = 27,
		Space = 32,
		Keypad0 = 256,
		Keypad1 = 257,
		Keypad2 = 258,
		Keypad3 = 259,
		Keypad4 = 260,
		Keypad5 = 261,
		Keypad6 = 262,
		Keypad7 = 263,
		Keypad8 = 264,
		Keypad9 = 265,
		KeypadPeriod = 266,
		KeypadDivide = 267,
		KeypadMultiply = 268,
		KeypadMinus = 269,
		KeypadPlus = 270,
		KeypadEnter = 271,
		KeypadEquals = 272,
		UpArrow = 273,
		DownArrow = 274,
		RightArrow = 275,
		LeftArrow = 276,
		Insert = 277,
		Home = 278,
		End = 279,
		PageUp = 280,
		PageDown = 281,
		F1 = 282,
		F2 = 283,
		F3 = 284,
		F4 = 285,
		F5 = 286,
		F6 = 287,
		F7 = 288,
		F8 = 289,
		F9 = 290,
		F10 = 291,
		F11 = 292,
		F12 = 293,
		F13 = 294,
		F14 = 295,
		F15 = 296,
		Alpha0 = 48,
		Alpha1 = 49,
		Alpha2 = 50,
		Alpha3 = 51,
		Alpha4 = 52,
		Alpha5 = 53,
		Alpha6 = 54,
		Alpha7 = 55,
		Alpha8 = 56,
		Alpha9 = 57,
		Exclaim = 33,
		DoubleQuote = 34,
		Hash = 35,
		Dollar = 36,
		Percent = 37,
		Ampersand = 38,
		Quote = 39,
		LeftParen = 40,
		RightParen = 41,
		Asterisk = 42,
		Plus = 43,
		Comma = 44,
		Minus = 45,
		Period = 46,
		Slash = 47,
		Colon = 58,
		Semicolon = 59,
		Less = 60,
		Equals = 61,
		Greater = 62,
		Question = 63,
		At = 64,
		LeftBracket = 91,
		Backslash = 92,
		RightBracket = 93,
		Caret = 94,
		Underscore = 95,
		BackQuote = 96,
		A = 97,
		B = 98,
		C = 99,
		D = 100,
		E = 101,
		F = 102,
		G = 103,
		H = 104,
		I = 105,
		J = 106,
		K = 107,
		L = 108,
		M = 109,
		N = 110,
		O = 111,
		P = 112,
		Q = 113,
		R = 114,
		S = 115,
		T = 116,
		U = 117,
		V = 118,
		W = 119,
		X = 120,
		Y = 121,
		Z = 122,
		LeftCurlyBracket = 123,
		Pipe = 124,
		RightCurlyBracket = 125,
		Tilde = 126,
		Numlock = 300,
		CapsLock = 301,
		ScrollLock = 302,
		RightShift = 303,
		LeftShift = 304,
		RightControl = 305,
		LeftControl = 306,
		RightAlt = 307,
		LeftAlt = 308,
		LeftMeta = 310,
		LeftCommand = 310,
		LeftApple = 310,
		LeftWindows = 311,
		RightMeta = 309,
		RightCommand = 309,
		RightApple = 309,
		RightWindows = 312,
		AltGr = 313,
		Help = 315,
		Print = 316,
		SysReq = 317,
		Break = 318,
		Menu = 319,
		Mouse0 = 323,
		Mouse1 = 324,
		Mouse2 = 325,
		Mouse3 = 326,
		Mouse4 = 327,
		Mouse5 = 328,
		Mouse6 = 329,
		JoystickButton0 = 330,
		JoystickButton1 = 331,
		JoystickButton2 = 332,
		JoystickButton3 = 333,
		JoystickButton4 = 334,
		JoystickButton5 = 335,
		JoystickButton6 = 336,
		JoystickButton7 = 337,
		JoystickButton8 = 338,
		JoystickButton9 = 339,
		JoystickButton10 = 340,
		JoystickButton11 = 341,
		JoystickButton12 = 342,
		JoystickButton13 = 343,
		JoystickButton14 = 344,
		JoystickButton15 = 345,
		JoystickButton16 = 346,
		JoystickButton17 = 347,
		JoystickButton18 = 348,
		JoystickButton19 = 349,
		Joystick1Button0 = 350,
		Joystick1Button1 = 351,
		Joystick1Button2 = 352,
		Joystick1Button3 = 353,
		Joystick1Button4 = 354,
		Joystick1Button5 = 355,
		Joystick1Button6 = 356,
		Joystick1Button7 = 357,
		Joystick1Button8 = 358,
		Joystick1Button9 = 359,
		Joystick1Button10 = 360,
		Joystick1Button11 = 361,
		Joystick1Button12 = 362,
		Joystick1Button13 = 363,
		Joystick1Button14 = 364,
		Joystick1Button15 = 365,
		Joystick1Button16 = 366,
		Joystick1Button17 = 367,
		Joystick1Button18 = 368,
		Joystick1Button19 = 369,
		Joystick2Button0 = 370,
		Joystick2Button1 = 371,
		Joystick2Button2 = 372,
		Joystick2Button3 = 373,
		Joystick2Button4 = 374,
		Joystick2Button5 = 375,
		Joystick2Button6 = 376,
		Joystick2Button7 = 377,
		Joystick2Button8 = 378,
		Joystick2Button9 = 379,
		Joystick2Button10 = 380,
		Joystick2Button11 = 381,
		Joystick2Button12 = 382,
		Joystick2Button13 = 383,
		Joystick2Button14 = 384,
		Joystick2Button15 = 385,
		Joystick2Button16 = 386,
		Joystick2Button17 = 387,
		Joystick2Button18 = 388,
		Joystick2Button19 = 389,
		Joystick3Button0 = 390,
		Joystick3Button1 = 391,
		Joystick3Button2 = 392,
		Joystick3Button3 = 393,
		Joystick3Button4 = 394,
		Joystick3Button5 = 395,
		Joystick3Button6 = 396,
		Joystick3Button7 = 397,
		Joystick3Button8 = 398,
		Joystick3Button9 = 399,
		Joystick3Button10 = 400,
		Joystick3Button11 = 401,
		Joystick3Button12 = 402,
		Joystick3Button13 = 403,
		Joystick3Button14 = 404,
		Joystick3Button15 = 405,
		Joystick3Button16 = 406,
		Joystick3Button17 = 407,
		Joystick3Button18 = 408,
		Joystick3Button19 = 409,
		Joystick4Button0 = 410,
		Joystick4Button1 = 411,
		Joystick4Button2 = 412,
		Joystick4Button3 = 413,
		Joystick4Button4 = 414,
		Joystick4Button5 = 415,
		Joystick4Button6 = 416,
		Joystick4Button7 = 417,
		Joystick4Button8 = 418,
		Joystick4Button9 = 419,
		Joystick4Button10 = 420,
		Joystick4Button11 = 421,
		Joystick4Button12 = 422,
		Joystick4Button13 = 423,
		Joystick4Button14 = 424,
		Joystick4Button15 = 425,
		Joystick4Button16 = 426,
		Joystick4Button17 = 427,
		Joystick4Button18 = 428,
		Joystick4Button19 = 429,
		Joystick5Button0 = 430,
		Joystick5Button1 = 431,
		Joystick5Button2 = 432,
		Joystick5Button3 = 433,
		Joystick5Button4 = 434,
		Joystick5Button5 = 435,
		Joystick5Button6 = 436,
		Joystick5Button7 = 437,
		Joystick5Button8 = 438,
		Joystick5Button9 = 439,
		Joystick5Button10 = 440,
		Joystick5Button11 = 441,
		Joystick5Button12 = 442,
		Joystick5Button13 = 443,
		Joystick5Button14 = 444,
		Joystick5Button15 = 445,
		Joystick5Button16 = 446,
		Joystick5Button17 = 447,
		Joystick5Button18 = 448,
		Joystick5Button19 = 449,
		Joystick6Button0 = 450,
		Joystick6Button1 = 451,
		Joystick6Button2 = 452,
		Joystick6Button3 = 453,
		Joystick6Button4 = 454,
		Joystick6Button5 = 455,
		Joystick6Button6 = 456,
		Joystick6Button7 = 457,
		Joystick6Button8 = 458,
		Joystick6Button9 = 459,
		Joystick6Button10 = 460,
		Joystick6Button11 = 461,
		Joystick6Button12 = 462,
		Joystick6Button13 = 463,
		Joystick6Button14 = 464,
		Joystick6Button15 = 465,
		Joystick6Button16 = 466,
		Joystick6Button17 = 467,
		Joystick6Button18 = 468,
		Joystick6Button19 = 469,
		Joystick7Button0 = 470,
		Joystick7Button1 = 471,
		Joystick7Button2 = 472,
		Joystick7Button3 = 473,
		Joystick7Button4 = 474,
		Joystick7Button5 = 475,
		Joystick7Button6 = 476,
		Joystick7Button7 = 477,
		Joystick7Button8 = 478,
		Joystick7Button9 = 479,
		Joystick7Button10 = 480,
		Joystick7Button11 = 481,
		Joystick7Button12 = 482,
		Joystick7Button13 = 483,
		Joystick7Button14 = 484,
		Joystick7Button15 = 485,
		Joystick7Button16 = 486,
		Joystick7Button17 = 487,
		Joystick7Button18 = 488,
		Joystick7Button19 = 489,
		Joystick8Button0 = 490,
		Joystick8Button1 = 491,
		Joystick8Button2 = 492,
		Joystick8Button3 = 493,
		Joystick8Button4 = 494,
		Joystick8Button5 = 495,
		Joystick8Button6 = 496,
		Joystick8Button7 = 497,
		Joystick8Button8 = 498,
		Joystick8Button9 = 499,
		Joystick8Button10 = 500,
		Joystick8Button11 = 501,
		Joystick8Button12 = 502,
		Joystick8Button13 = 503,
		Joystick8Button14 = 504,
		Joystick8Button15 = 505,
		Joystick8Button16 = 506,
		Joystick8Button17 = 507,
		Joystick8Button18 = 508,
		Joystick8Button19 = 509,
		SHIT_MOUSE1 = 900,
		SHIT_MOUSE2 = 901,
		SHIT_MOUSE3 = 902,
	};

	enum class EventType : int {
		MouseDown = 0,
		MouseUp = 1,
		MouseMove = 2,
		MouseDrag = 3,
		KeyDown = 4,
		KeyUp = 5,
		ScrollWheel = 6,
		Repaint = 7,
		Layout = 8,
		DragUpdated = 9,
		DragPerform = 10,
		DragExited = 15,
		Ignore = 11,
		Used = 12,
		ValidateCommand = 13,
		ExecuteCommand = 14,
		ContextClick = 16,
		MouseEnterWindow = 20,
		MouseLeaveWindow = 21
	};


	enum TextAnchor // TypeDefIndex: 13727
	{
		// Fields
		UpperLeft = 0,
		UpperCenter = 1,
		UpperRight = 2,
		MiddleLeft = 3,
		MiddleCenter = 4,
		MiddleRight = 5,
		LowerLeft = 6,
		LowerCenter = 7,
		LowerRight = 8,
	};


	enum LifeState // TypeDefIndex: 8866
	{
		Alive = 0,
		Dead = 1
	};

	enum AmbientMode // TypeDefIndex: 10709
	{
		// Fields
		Skybox = 0,
		Trilight = 1,
		Flat = 3,
		Custom = 4
	};

	enum class ItemCategory : std::int32_t
	{
		Weapon,
		Construction,
		Items,
		Resources,
		Attire,
		Tool,
		Medical,
		Food,
		Ammunition,
		Traps,
		Misc,
		All,
		Common,
		Component,
		Search,
		Favourite,
		Electrical,
		Fun,
	};

	enum class Layers
	{
		Terrain = 8388608,
		World = 65536,
		Ragdolls = 512,
		Construction = 2097152,
		ConstructionSocket = 4194304,
		Craters = 1,
		GameTrace = 16384,
		Trigger = 262144,
		VehiclesDetailed = 8192,
		RainFall = 1101070337,
		Deploy = 1235288065,
		DefaultDeployVolumeCheck = 537001984,
		BuildLineOfSightCheck = 2097152,
		ProjectileLineOfSightCheck = 2162688,
		ProjectileLineOfSightCheckTerrain = 10551296,
		MeleeLineOfSightCheck = 2162688,
		EyeLineOfSightCheck = 2162688,
		EntityLineOfSightCheck = 1218519041,
		PlayerBuildings = 18874624,
		PlannerPlacement = 161546496,
		Solid = 1218652417,
		VisCulling = 10551297,
		AltitudeCheck = 1218511105,
		HABGroundEffect = 1218511105,
		AILineOfSight = 1218519297,
		DismountCheck = 1486946561,
		AIPlacement = 278986753,
		WheelRay = 1235321089,
		z = 1503731969,
	};

	enum GlMode : int { //primitive_mode
		Lines = 1,
		Line_Strip,
		Trangles = 4,
		Trangle_Strip,
		Quads = 7
	};

	enum QueryTriggerInteraction // TypeDefIndex: 13253
	{
		UseGlobal = 0,
		Ignore = 1,
		Collide = 2,
	};

	enum TextAlignmentOptions // TypeDefIndex: 11475
	{
		// Fields
		TopLeft = 257,
		Top = 258,
		TopRight = 260,
		TopJustified = 264,
		TopFlush = 272,
		TopGeoAligned = 288,
		Left = 513,
		Center = 514,
		Right = 516,
		Justified = 520,
		Flush = 528,
		CenterGeoAligned = 544,
		BottomLeft = 1025,
		Bottom = 1026,
		BottomRight = 1028,
		BottomJustified = 1032,
		BottomFlush = 1040,
		BottomGeoAligned = 1056,
		BaselineLeft = 2049,
		Baseline = 2050,
		BaselineRight = 2052,
		BaselineJustified = 2056,
		BaselineFlush = 2064,
		BaselineGeoAligned = 2080,
		MidlineLeft = 4097,
		Midline = 4098,
		MidlineRight = 4100,
		MidlineJustified = 4104,
		MidlineFlush = 4112,
		MidlineGeoAligned = 4128,
		CaplineLeft = 8193,
		Capline = 8194,
		CaplineRight = 8196,
		CaplineJustified = 8200,
		CaplineFlush = 8208,
		CaplineGeoAligned = 8224,
	};

	enum TextureCreationFlags // TypeDefIndex: 10774
	{
		// Fields
		None1 = 0,
		MipChain = 1,
		Crunch = 64,
	};

	enum TextureFormat // TypeDefIndex: 10276
	{
		// Fields

		Alpha88 = 1,
		ARGB4444 = 2,
		RGB24 = 3,
		RGBA32 = 4,
		ARGB32 = 5,
		RGB565 = 7,
		R16 = 9,
		DXT1 = 10,
		DXT5 = 12,
		RGBA4444 = 13,
		BGRA32 = 14,
		RHalf = 15,
		RGHalf = 16,
		RGBAHalf = 17,
		RFloat = 18,
		RGFloat = 19,
		RGBAFloat = 20,
		YUY2 = 21,
		RGB9e5Float = 22,
		BC4 = 26,
		BC5 = 27,
		BC6H = 24,
		BC7 = 25,
		DXT1Crunched = 28,
		DXT5Crunched = 29,
		PVRTC_RGB2 = 30,
		PVRTC_RGBA2 = 31,
		PVRTC_RGB4 = 32,
		PVRTC_RGBA4 = 33,
		ETC_RGB4 = 34,
		EAC_R = 41,
		EAC_R_SIGNED = 42,
		EAC_RG = 43,
		EAC_RG_SIGNED = 44,
		ETC2_RGB = 45,
		ETC2_RGBA1 = 46,
		ETC2_RGBA8 = 47,
		ASTC_4x4 = 48,
		ASTC_5x5 = 49,
		ASTC_6x6 = 50,
		ASTC_8x8 = 51,
		ASTC_10x10 = 52,
		ASTC_12x12 = 53,
		ETC_RGB4_3DS = 60,
		ETC_RGBA8_3DS = 61,
		RG16 = 62,
		R8 = 63,
		ETC_RGB4Crunched = 64,
		ETC2_RGBA8Crunched = 65,
		ASTC_HDR_4x4 = 66,
		ASTC_HDR_5x5 = 67,
		ASTC_HDR_6x6 = 68,
		ASTC_HDR_8x8 = 69,
		ASTC_HDR_10x10 = 70,
		ASTC_HDR_12x12 = 71,
		RG32 = 72,
		RGB48 = 73,
		RGBA64 = 74,
		ASTC_RGB_4x4 = 48,
		ASTC_RGB_5x5 = 49,
		ASTC_RGB_6x6 = 50,
		ASTC_RGB_8x8 = 51,
		ASTC_RGB_10x10 = 52,
		ASTC_RGB_12x12 = 53,
		ASTC_RGBA_4x4 = 54,
		ASTC_RGBA_5x5 = 55,
		ASTC_RGBA_6x6 = 56,
		ASTC_RGBA_8x8 = 57,
		ASTC_RGBA_10x10 = 58,
		ASTC_RGBA_12x12 = 59,
	};

	enum GraphicsFormat // TypeDefIndex: 10777
	{
		// Fields
		None2 = 0,
		R8_SRGB = 1,
		R8G8_SRGB = 2,
		R8G8B8_SRGB = 3,
		R8G8B8A8_SRGB = 4,
		R8_UNorm = 5,
		R8G8_UNorm = 6,
		R8G8B8_UNorm = 7,
		R8G8B8A8_UNorm = 8,
		R8_SNorm = 9,
		R8G8_SNorm = 10,
		R8G8B8_SNorm = 11,
		R8G8B8A8_SNorm = 12,
		R8_UInt = 13,
		R8G8_UInt = 14,
		R8G8B8_UInt = 15,
		R8G8B8A8_UInt = 16,
		R8_SInt = 17,
		R8G8_SInt = 18,
		R8G8B8_SInt = 19,
		R8G8B8A8_SInt = 20,
		R16_UNorm = 21,
		R16G16_UNorm = 22,
		R16G16B16_UNorm = 23,
		R16G16B16A16_UNorm = 24,
		R16_SNorm = 25,
		R16G16_SNorm = 26,
		R16G16B16_SNorm = 27,
		R16G16B16A16_SNorm = 28,
		R16_UInt = 29,
		R16G16_UInt = 30,
		R16G16B16_UInt = 31,
		R16G16B16A16_UInt = 32,
		R16_SInt = 33,
		R16G16_SInt = 34,
		R16G16B16_SInt = 35,
		R16G16B16A16_SInt = 36,
		R32_UInt = 37,
		R32G32_UInt = 38,
		R32G32B32_UInt = 39,
		R32G32B32A32_UInt = 40,
		R32_SInt = 41,
		R32G32_SInt = 42,
		R32G32B32_SInt = 43,
		R32G32B32A32_SInt = 44,
		R16_SFloat = 45,
		R16G16_SFloat = 46,
		R16G16B16_SFloat = 47,
		R16G16B16A16_SFloat = 48,
		R32_SFloat = 49,
		R32G32_SFloat = 50,
		R32G32B32_SFloat = 51,
		R32G32B32A32_SFloat = 52,
		B8G8R8_SRGB = 56,
		B8G8R8A8_SRGB = 57,
		B8G8R8_UNorm = 58,
		B8G8R8A8_UNorm = 59,
		B8G8R8_SNorm = 60,
		B8G8R8A8_SNorm = 61,
		B8G8R8_UInt = 62,
		B8G8R8A8_UInt = 63,
		B8G8R8_SInt = 64,
		B8G8R8A8_SInt = 65,
		R4G4B4A4_UNormPack16 = 66,
		B4G4R4A4_UNormPack16 = 67,
		R5G6B5_UNormPack16 = 68,
		B5G6R5_UNormPack16 = 69,
		R5G5B5A1_UNormPack16 = 70,
		B5G5R5A1_UNormPack16 = 71,
		A1R5G5B5_UNormPack16 = 72,
		E5B9G9R9_UFloatPack32 = 73,
		B10G11R11_UFloatPack32 = 74,
		A2B10G10R10_UNormPack32 = 75,
		A2B10G10R10_UIntPack32 = 76,
		A2B10G10R10_SIntPack32 = 77,
		A2R10G10B10_UNormPack32 = 78,
		A2R10G10B10_UIntPack32 = 79,
		A2R10G10B10_SIntPack32 = 80,
		A2R10G10B10_XRSRGBPack32 = 81,
		A2R10G10B10_XRUNormPack32 = 82,
		R10G10B10_XRSRGBPack32 = 83,
		R10G10B10_XRUNormPack32 = 84,
		A10R10G10B10_XRSRGBPack32 = 85,
		A10R10G10B10_XRUNormPack32 = 86,
		D16_UNorm = 90,
		D24_UNorm = 91,
		D24_UNorm_S8_UInt = 92,
		D32_SFloat = 93,
		D32_SFloat_S8_UInt = 94,
		S8_UInt = 95,
		RGB_DXT1_SRGB = 96,
		RGBA_DXT1_SRGB = 96,
		RGB_DXT1_UNorm = 97,
		RGBA_DXT1_UNorm = 97,
		RGBA_DXT3_SRGB = 98,
		RGBA_DXT3_UNorm = 99,
		RGBA_DXT5_SRGB = 100,
		RGBA_DXT5_UNorm = 101,
		R_BC4_UNorm = 102,
		R_BC4_SNorm = 103,
		RG_BC5_UNorm = 104,
		RG_BC5_SNorm = 105,
		RGB_BC6H_UFloat = 106,
		RGB_BC6H_SFloat = 107,
		RGBA_BC7_SRGB = 108,
		RGBA_BC7_UNorm = 109,
		RGB_PVRTC_2Bpp_SRGB = 110,
		RGB_PVRTC_2Bpp_UNorm = 111,
		RGB_PVRTC_4Bpp_SRGB = 112,
		RGB_PVRTC_4Bpp_UNorm = 113,
		RGBA_PVRTC_2Bpp_SRGB = 114,
		RGBA_PVRTC_2Bpp_UNorm = 115,
		RGBA_PVRTC_4Bpp_SRGB = 116,
		RGBA_PVRTC_4Bpp_UNorm = 117,
		RGB_ETC_UNorm = 118,
		RGB_ETC2_SRGB = 119,
		RGB_ETC2_UNorm = 120,
		RGB_A1_ETC2_SRGB = 121,
		RGB_A1_ETC2_UNorm = 122,
		RGBA_ETC2_SRGB = 123,
		RGBA_ETC2_UNorm = 124,
		R_EAC_UNorm = 125,
		R_EAC_SNorm = 126,
		RG_EAC_UNorm = 127,
		RG_EAC_SNorm = 128,
		RGBA_ASTC4X4_SRGB = 129,
		RGBA_ASTC4X4_UNorm = 130,
		RGBA_ASTC5X5_SRGB = 131,
		RGBA_ASTC5X5_UNorm = 132,
		RGBA_ASTC6X6_SRGB = 133,
		RGBA_ASTC6X6_UNorm = 134,
		RGBA_ASTC8X8_SRGB = 135,
		RGBA_ASTC8X8_UNorm = 136,
		RGBA_ASTC10X10_SRGB = 137,
		RGBA_ASTC10X10_UNorm = 138,
		RGBA_ASTC12X12_SRGB = 139,
		RGBA_ASTC12X12_UNorm = 140,
		YUV2 = 141,
		DepthAuto = 142,
		ShadowAuto = 143,
		VideoAuto = 144,
		RGBA_ASTC4X4_UFloat = 145,
		RGBA_ASTC5X5_UFloat = 146,
		RGBA_ASTC6X6_UFloat = 147,
		RGBA_ASTC8X8_UFloat = 148,
		RGBA_ASTC10X10_UFloat = 149,
		RGBA_ASTC12X12_UFloat = 150,
	};

	enum BuildingGrade // TypeDefIndex: 2559
	{
		// Fields
		None = -1,
		Twigs = 0,
		Wood = 1,
		Stone = 2,
		Metal = 3,
		TopTier = 4,
		Count = 5,
	};
	
	enum PlayerFlags
	{
		Unused1 = 1,
		Unused2 = 2,
		IsAdmin = 4,
		ReceivingSnapshot = 8,
		Sleeping = 16,
		Spectating = 32,
		Wounded = 64,
		IsDeveloper = 128,
		Connected = 256,
		ThirdPersonViewmode = 1024,
		EyesViewmode = 2048,
		ChatMute = 4096,
		NoSprint = 8192,
		Aiming = 16384,
		DisplaySash = 32768,
		Relaxed = 65536,
		SafeZone = 131072,
		ServerFall = 262144,
		Workbench1 = 1048576,
		Workbench2 = 2097152,
		Workbench3 = 4194304
	};

	enum bones
	{
		l_hip = 1,
		l_knee,
		l_foot,
		l_toe,
		l_ankle_scale,
		pelvis,
		penis,
		GenitalCensor,
		GenitalCensor_LOD0,
		Inner_LOD0,
		GenitalCensor_LOD1,
		GenitalCensor_LOD2,
		r_hip,
		r_knee,
		r_foot,
		r_toe,
		r_ankle_scale,
		spine1,
		spine1_scale,
		spine2,
		spine3,
		spine4,
		l_clavicle,
		l_upperarm,
		l_forearm,
		l_hand,
		l_index1,
		l_index2,
		l_index3,
		l_little1,
		l_little2,
		l_little3,
		l_middle1,
		l_middle2,
		l_middle3,
		l_prop,
		l_ring1,
		l_ring2,
		l_ring3,
		l_thumb1,
		l_thumb2,
		l_thumb3,
		IKtarget_righthand_min,
		IKtarget_righthand_max,
		l_ulna,
		neck,
		head,
		jaw,
		eyeTranform,
		l_eye,
		l_Eyelid,
		r_eye,
		r_Eyelid,
		r_clavicle,
		r_upperarm,
		r_forearm,
		r_hand,
		r_index1,
		r_index2,
		r_index3,
		r_little1,
		r_little2,
		r_little3,
		r_middle1,
		r_middle2,
		r_middle3,
		r_prop,
		r_ring1,
		r_ring2,
		r_ring3,
		r_thumb1,
		r_thumb2,
		r_thumb3,
		IKtarget_lefthand_min,
		IKtarget_lefthand_max,
		r_ulna,
		l_breast,
		r_breast,
		BoobCensor,
		BreastCensor_LOD0,
		BreastCensor_LOD1,
		BreastCensor_LOD2,
		collision,
		displacement
	};

	enum BaseEntity_Flags // TypeDefIndex: 266
	{
		// Fields
		Placeholder = 1,
		On = 2,
		OnFire = 4,
		Open = 8,
		Locked = 16,
		Debugging = 32,
		Disabled = 64,
		Reserved1 = 128,
		Reserved2 = 256,
		Reserved3 = 512,
		Reserved4 = 1024,
		Reserved5 = 2048,
		Broken = 4096,
		Busy = 8192,
		Reserved6 = 16384,
		Reserved7 = 32768,
		Reserved8 = 65536,
		Reserved9 = 131072,
		Reserved10 = 262144,
		Reserved11 = 524288,
		InUse = 1048576
	};
}