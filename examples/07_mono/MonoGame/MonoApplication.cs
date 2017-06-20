/*
 * Copyright (c) 2012-2017 Robin Degen
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

using System;
using AeonEngineMono.Assets;
using AeonEngineMono.Gfx;
using AeonEngineMono.Input;
using AeonEngineMono.Resources;
using AeonEngineMono.Scene;
using AeonEngineMono.Types;
using AeonEngineMono.Window;

public class MonoApplication
{
    private const int MoveSouth = 0;
    private const int MoveWest = 1;
    private const int MoveEast = 2;
    private const int MoveNorth = 3;

    private const float ValheimSpeed = 40;

    private OrthographicCamera _camera;
    private Viewport _viewport;
    private SceneNode _shipNode;

    private AnimatedSprite _valheim;
    private SceneNode _valheimNode;
    private int _valheimDirection = MoveSouth;

    public MonoApplication()
    {
        Console.WriteLine("MonoApplication created.");
    }

    ~MonoApplication()
    {
        Console.WriteLine("MonoApplication destroyed.");
    }

    public void Initialize()
    {
        Console.WriteLine("Initializing game engine!");
        Console.WriteLine("Window title: " + Window.Title);

        Input.CursorMode = MouseCursorMode.Normal;

        ResourceManager.Mount(new FilesystemCollectionProvider("."), "/");

        _camera = new OrthographicCamera(0, 1280, 720, 0);
        _viewport = new Viewport(_camera, "My Viewport");

        _shipNode = new SceneNode("ShipNode");
        SceneManager.RootSceneNode.AttachChild(_shipNode);

        //_shipNode.SetPosition(400, 300);

        Material material = new Material("/resources/materials/ships.amf");
        Atlas atlas = new Atlas(material, new Vector2f(64, 64));
        AtlasRegion shipRegion = atlas.GetRegionByIndex(10);

        Sprite sprite = new Sprite(shipRegion, 0, "My Ship");
        _shipNode.AttachComponent(sprite);

        Material animationMaterial = new Material("/resources/materials/valheim.amf");
        Atlas animationAtlas = new Atlas(animationMaterial, new Vector2f(32, 32));

        SpriteAnimationSettings settings = new SpriteAnimationSettings(new Vector2f(32, 32));
        settings.GenerateSequence(MoveSouth, 3, 3, AnimationSequenceType.UpDown);
        settings.GenerateSequence(MoveWest, 15, 3, AnimationSequenceType.UpDown);
        settings.GenerateSequence(MoveEast, 27, 3, AnimationSequenceType.UpDown);
        settings.GenerateSequence(MoveNorth, 39, 3, AnimationSequenceType.UpDown);
        settings.StartCondition = AnimationStartCondition.ManualStart;
        settings.Speed = 0.2f;
        settings.Repeat = AnimationRepeat.Continuous;

        _valheimNode = new SceneNode("Valheim");
        SceneManager.RootSceneNode.AttachChild(_valheimNode);

        _valheim = new AnimatedSprite(animationAtlas, 0, settings, "Valheim");
        _valheimNode.AttachComponent(_valheim);

        _valheimNode.SetPosition(30, 30);

        Input.BindButton("fire", KeyboardKey.KeySpace);
        Input.BindButton("fire", MouseButton.MouseButtonLeft);
        Input.BindButton("fire", KeyboardKey.KeyE);
    }

    public bool Update(float dt)
    {
        if (Input.GetKeyDown(KeyboardKey.KeyR))
        {
            Console.WriteLine("R key down.");
        }

        if (Input.GetKeyUp(KeyboardKey.KeyR))
        {
            Console.WriteLine("R key up.");
        }

        if (Input.GetButtonDown("fire"))
        {
            Console.WriteLine("Fire exclamationmark.");
        }

        if (Input.GetButtonUp("fire"))
        {
            Console.WriteLine("No more fire.");
        }

        if (Input.GetKeystate(KeyboardKey.KeyEscape) == KeyboardKeyState.Pressed)
        {
            return false;
        }

        if (Input.GetKeystate(KeyboardKey.KeyDown) == KeyboardKeyState.Pressed)
        {
            if (_valheimDirection != MoveSouth)
            {
                _valheimDirection = MoveSouth;
                _valheim.AnimationSequence = _valheimDirection;

            }

            _valheim.Run();
            _valheimNode.Translate(0, dt * ValheimSpeed);
        }
        else if (Input.GetKeystate(KeyboardKey.KeyUp) == KeyboardKeyState.Pressed)
        {
            if (_valheimDirection != MoveNorth)
            {
                _valheimDirection = MoveNorth;
                _valheim.AnimationSequence = _valheimDirection;
            }

            _valheim.Run();
            _valheimNode.Translate(0, -dt * ValheimSpeed);
        }
        else if (Input.GetKeystate(KeyboardKey.KeyLeft) == KeyboardKeyState.Pressed)
        {
            if (_valheimDirection != MoveWest)
            {
                _valheimDirection = MoveWest;
                _valheim.AnimationSequence = _valheimDirection;
            }

            _valheim.Run();
            _valheimNode.Translate(-dt * ValheimSpeed, 0);
        }
        else if (Input.GetKeystate(KeyboardKey.KeyRight) == KeyboardKeyState.Pressed)
        {
            if (_valheimDirection != MoveEast)
            {
                _valheimDirection = MoveEast;
                _valheim.AnimationSequence = _valheimDirection;

            }

            _valheim.Run();
            _valheimNode.Translate(dt * ValheimSpeed, 0);
        }
        else
        {
            _valheim.Stop();
        }

        if (Input.GetMouseButtonState(MouseButton.MouseButtonLeft) == MouseButtonState.Pressed)
        {
            _shipNode.Position = Input.GetMouseCursorPosition();
        }

        return true;
    }
}
