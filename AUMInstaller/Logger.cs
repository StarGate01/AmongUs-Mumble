using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace AUMInstaller
{
    class Logger
    {

        private FormMain formMain;

        public Logger(FormMain form)
        {
            formMain = form;
            Reset();
        }

        public void Reset()
        {
            formMain.progressBarInstall.Value = 0;
        }

        public void Log(string message)
        {
            // Use invoke to make this method thread-safe
            formMain.listBoxLog.Invoke((MethodInvoker)delegate
            {
                formMain.listBoxLog.Items.Add(message);
                // Scroll to bottom
                formMain.listBoxLog.TopIndex = formMain.listBoxLog.Items.Count - 1;
            });
        }

        public void CompleteStep(int steps = 1)
        {
            // Use invoke to make this method thread-safe
            formMain.progressBarInstall.Invoke((MethodInvoker)delegate
            {
                formMain.progressBarInstall.Step = steps;
                formMain.progressBarInstall.PerformStep();
            });
        }

    }
}
