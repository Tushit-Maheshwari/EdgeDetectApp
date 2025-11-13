class EdgeDetectViewer {
    private canvas: HTMLCanvasElement;
    private ctx: CanvasRenderingContext2D;
    
    constructor() {
        this.canvas = document.getElementById('frameCanvas') as HTMLCanvasElement;
        this.ctx = this.canvas.getContext('2d')!;
        this.displaySample();
    }
    
    private displaySample(): void {
        const tempCanvas = document.createElement('canvas');
        tempCanvas.width = 640;
        tempCanvas.height = 480;
        const tempCtx = tempCanvas.getContext('2d')!;
        
        tempCtx.fillStyle = 'black';
        tempCtx.fillRect(0, 0, 640, 480);
        tempCtx.strokeStyle = 'white';
        tempCtx.lineWidth = 2;
        tempCtx.strokeRect(100, 100, 200, 150);
        
        const img = new Image();
        img.onload = () => {
            this.canvas.width = 640;
            this.canvas.height = 480;
            this.ctx.drawImage(img, 0, 0);
        };
        img.src = tempCanvas.toDataURL();
    }
}

document.addEventListener('DOMContentLoaded', () => {
    new EdgeDetectViewer();
});
