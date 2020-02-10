import QtQuick 2.0



Rectangle {
    //property int size: 200

    //width: size
    height: width*3

    function min(lhs,rhs){
        return lhs < rhs ? lhs:rhs;
    }

    function euclidDist(x1,y1,x2,y2){
        var dx = x1-x2;
        var dy = y1-y2;
        return Math.sqrt(Math.pow(dx,2) + Math.pow(dy,2))
    }


    property real arcBegin: 0 //don't change
    property real arcEnd: 360 //maximum value
    property real arcOffset: -90 //shift sector (from arcBegin to arcEnd)  on circle
    property real angle: 0 //current value in deg
    property real scaleFactor: 0.8
    property real bigCircleRadius: (min(width,height) / 6) * scaleFactor
    property real smallCircleRadius: bigCircleRadius * 0.15
    property real smallestCircleRadius: bigCircleRadius * 0.09

    property real pistonHeight: height*0.2
    property real pistonWidth: bigCircleRadius
    property real pistonStep: (bigCircleRadius*2) / 180.0
    property real pistDelta: 0.

    property int lineWidth: 5
    property string colorCircle: "rgba(255, 127, 80, 0.99)";
    property string colorArrow: "rgba(128, 128, 128, 1.0)";

    onAngleChanged: {
        if (angle < arcBegin)
            angle = 360 + angle;
        else if (angle > arcEnd)
            angle = angle % 360;

        if (angle < 180.0)
            pistDelta = angle*pistonStep;
        else
            pistDelta = (360.0 - angle)*pistonStep;

        gaugeCanvas.requestPaint();
    }

    onArcBeginChanged: {
        arcBegin = 0;
    }

    onArcEndChanged: {
        if (arcEnd < 0)
            arcEnd = 0;
        else if (arcEnd > 180)
            arcEnd = 180;
    }

    Canvas{
        id: gaugeCanvas
        anchors.fill: parent

        function drawFilledCircle(ctx, centerX, centerY, radius, color){
            ctx.beginPath();
            ctx.strokeStyle = color;
            ctx.fillStyle = color;
            ctx.lineWidth = parent.lineWidth;
            ctx.arc(centerX, centerY, radius, 0, Math.PI * 2);
            ctx.fill();
        }

        function deg2rad(deg){
            return (deg * Math.PI) / 180.0;
        }

        function drawDashedLine(ctx, startX, startY, endX, endY){
            ctx.beginPath();
            ctx.strokeStyle = parent.colorArrow;
            ctx.fillStyle = parent.colorArrow;
            ctx.lineWidth = parent.lineWidth / 2;
            //ctx.setLineDash([5, 5]);
            ctx.moveTo(startX, startY);
            ctx.lineTo(endX, endY);
            ctx.stroke();
            ctx.setLineDash([1,0]); // to paint solid line after dashed
        }

        onPaint: {
            var ctx = getContext('2d');

            //draw big circle
            var centerX = width / 2;
            var centerY = height * 0.75;

            ctx.clearRect(0, 0, gaugeCanvas.width, gaugeCanvas.height);

            ctx.beginPath();

            //========================draw circle===============================
            ctx.strokeStyle = parent.colorCircle;
            ctx.fillStyle = parent.colorCircle;
            ctx.lineWidth = parent.lineWidth;
            ctx.arc(centerX, centerY, parent.bigCircleRadius, 0, Math.PI * 2);
            ctx.stroke();

            //draw arcBegin
            var angle = deg2rad(parent.arcBegin + parent.arcOffset);

            //draw line
            angle = deg2rad(parent.angle + parent.arcOffset);

            drawDashedLine(ctx, centerX, centerY,
                           centerX + (parent.bigCircleRadius * Math.cos(angle)),
                           centerY + (parent.bigCircleRadius * Math.sin(angle)))

            //draw start of arrow
            drawFilledCircle(ctx,
                             centerX,
                             centerY,
                             parent.smallestCircleRadius,
                             parent.colorArrow);

            //==============draw=piston=========================================

            ctx.beginPath();

            drawDashedLine(ctx,
                           centerX + (parent.bigCircleRadius * Math.cos(angle)),
                           centerY + (parent.bigCircleRadius * Math.sin(angle)),
                           centerX,
                           10 + pistDelta + pistonHeight)

            var dist = euclidDist(centerX + (parent.bigCircleRadius * Math.cos(angle)),
                                  centerY + (parent.bigCircleRadius * Math.sin(angle)),
                                  centerX,
                                  10 + pistDelta + pistonHeight)
            console.log("euclid dist = ", dist)

            ctx.fillRect(centerX - (pistonWidth / 2), 10+pistDelta,
                         pistonWidth, pistonHeight)

            console.log("Top y = ", 10+pistDelta, " radius = ", parent.bigCircleRadius)


            //draw value circle
            drawFilledCircle(ctx,
                             centerX + (parent.bigCircleRadius * Math.cos(angle)),
                             centerY + (parent.bigCircleRadius * Math.sin(angle)),
                             parent.smallCircleRadius,
                             parent.colorCircle);
        }
    }
}


