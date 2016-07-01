<GameFile>
  <PropertyGroup Name="Tile" Type="Node" ID="8b673f38-e242-423a-b527-be0ad80a45d4" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="0.5000" ActivedAnimationName="popBg">
        <Timeline ActionTag="776945374" Property="Position">
          <PointFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="8" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="11" X="0.0000" Y="0.0000">
            <EasingData Type="5" />
          </PointFrame>
          <PointFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="5" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="776945374" Property="Scale">
          <ScaleFrame FrameIndex="0" X="0.3000" Y="0.3000">
            <EasingData Type="8" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="11" X="1.0000" Y="1.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="1.1000" Y="1.1000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="1.0000" Y="1.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
        <Timeline ActionTag="776945374" Property="RotationSkew">
          <ScaleFrame FrameIndex="0" X="0.0000" Y="0.0000">
            <EasingData Type="8" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="10" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="11" X="0.0000" Y="0.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="15" X="0.0000" Y="0.0000">
            <EasingData Type="5" />
          </ScaleFrame>
          <ScaleFrame FrameIndex="20" X="0.0000" Y="0.0000">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <AnimationList>
        <AnimationInfo Name="default" StartIndex="0" EndIndex="0">
          <RenderColor A="255" R="238" G="232" B="170" />
        </AnimationInfo>
        <AnimationInfo Name="popBg" StartIndex="11" EndIndex="21">
          <RenderColor A="255" R="138" G="43" B="226" />
        </AnimationInfo>
        <AnimationInfo Name="show" StartIndex="0" EndIndex="10">
          <RenderColor A="255" R="224" G="255" B="255" />
        </AnimationInfo>
      </AnimationList>
      <ObjectData Name="Node" CustomClassName="Tile2048" Tag="17" ctype="GameNodeObjectData">
        <Size X="0.0000" Y="0.0000" />
        <Children>
          <AbstractNodeData Name="bg" ActionTag="776945374" Tag="47" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="-65.0000" RightMargin="-65.0000" TopMargin="-65.0000" BottomMargin="-65.0000" ctype="SpriteObjectData">
            <Size X="130.0000" Y="130.0000" />
            <Children>
              <AbstractNodeData Name="numberText" ActionTag="-738620425" Tag="30" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="4.5000" RightMargin="4.5000" TopMargin="31.0000" BottomMargin="31.0000" FontSize="50" LabelText="2048" ShadowOffsetX="1.0000" ShadowOffsetY="-1.0000" ShadowEnabled="True" ctype="TextObjectData">
                <Size X="121.0000" Y="68.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="65.0000" Y="65.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.9308" Y="0.5231" />
                <FontResource Type="Normal" Path="Assets/Fonts/ClearSans-Bold.ttf" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="Assets/Images/tile_128.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>